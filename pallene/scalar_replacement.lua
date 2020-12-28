-- Copyright (c) 2020, The Pallene Developers
-- Pallene is licensed under the MIT license.
-- Please refer to the LICENSE and AUTHORS files for details
-- SPDX-License-Identifier: MIT

local ir = require "pallene.ir"
local typedecl = require "pallene.typedecl"
local inspect = require"inspect"
local scalar_replacement = {}



local function is_constant_value(v)
    local tag = v._tag
    if     tag == "ir.Value.Nil"      then return true
    elseif tag == "ir.Value.Bool"     then return true
    elseif tag == "ir.Value.Integer"  then return true
    elseif tag == "ir.Value.Float"    then return true
    elseif tag == "ir.Value.String"   then return true
    elseif tag == "ir.Value.LocalVar" then return false
    elseif tag == "ir.Value.Function" then return true
    else
        typedecl.tag_error(tag)
    end
end

-- Replaces constant table values for constants
local function AVal(cmd,state)

end
local function AEval(root_cmd)
    local state = {}
    local states = {}
    local f = function(cmd)
        local tag = cmd._tag
        if     tag == "ir.Cmd.Move" then
            --print(inspect(cmd))
            if not state[cmd.dst] then
                if is_constant_value(cmd.src) then
                    state[cmd.dst] = cmd.src
                else
                    assert(false,'assigning non constant, should be treated')
                end
            end
        elseif     tag == "ir.Cmd.SetArr" then
            if not state[cmd.src_arr.id] then
                state[cmd.src_arr.id] = {}
            end
            if     cmd.src_i._tag == "ir.Value.Integer" then
                state[cmd.src_arr.id][cmd.src_i.value] = {value = cmd.src_v.value, _tag = cmd.src_i._tag}
            elseif cmd.src_i._tag == "ir.Value.LocalVar" then
                state[cmd.src_arr.id][cmd.src_i.id] = {cmd.src_v.value, _tag = cmd.src_i._tag}
            end
        elseif     tag == "ir.Cmd.CallStatic" then
            -- TODO also CallDyn
            if not state.escaped then
                state.escaped = {}
            end
            for k,v in ipairs(cmd.srcs) do
                state.escaped[#state.escaped+1] = v
            end
            --print(inspect(cmd))
        else
                print(tag)
        end

    end
    local join = function(ctx1,ctx2) return ctx1 end
    local function go(cmd,ctx)
        -- Transform child nodes recursively
        states[#states+1] = state
        local tag = cmd._tag
        if     tag == "ir.Cmd.Seq" then
            for i = 1, #cmd.cmds do
                ctx = join(go(cmd.cmds[i],ctx),ctx)
            end
        elseif tag == "ir.Cmd.If" then
            local ctx_then_ = join(go(cmd.then_,ctx),ctx)
            local ctx_else_ = join(go(cmd.else_,ctx),ctx)
            ctx = join(ctx_then_,ctx_else_)
        elseif tag == "ir.Cmd.Loop" then
            --cmd.body = go(cmd.body)
        elseif tag == "ir.Cmd.For" then
            --cmd.body = go(cmd.body)
        else
            -- no child nodes

        end

        -- Transform parent node
        return f(cmd) or cmd
    end
    local last = go(root_cmd,state)
    states[#states+1] = last
    return states
end

function clean_new_table(cmd)
    -- make a map of array id and number of accesses
    -- if accesses is 0, can remove newarr
    --TODO find a way to clean CheckGC()
    local uses = {}
    ir.map_cmd(cmd,function(_cmd)
        if _cmd._tag == "ir.Cmd.GetArr" then
            if not uses[_cmd.src_arr.id] then
                uses[_cmd.src_arr.id] = 0
            end
            uses[_cmd.src_arr.id] = uses[_cmd.src_arr.id] + 1
        end
    end)
    ir.map_cmd(cmd,function(_cmd)
        if _cmd._tag == "ir.Cmd.NewArr" then
            if not uses[_cmd.dst] then
                return ir.Cmd.Nop()
            end
        end
        if _cmd._tag == "ir.Cmd.SetArr" then
            if not uses[_cmd.src_arr.id] then
                return ir.Cmd.Nop()
            end
        end
    end)
end

local function contains_id(arr,item)
    for k,v in ipairs(arr) do
        if v.id == item then return true end
    end
    return false
end


-- the main idea is to replace getarr for temporary variables.
-- a possible repercussion of this is to be able to remove the array altogether
-- a getarr can be turned into a temporary variable if the array doesn't escape
-- to apply the transformation, one can create a new variable, setting it to the
-- last known value

-- we will be doing an abstract interpretation with the domain being
-- A = {Luavalue,localvar,_,?}, _ being bot = undefined and ? being top = non-constant.
-- the program state at each node will be a map of
-- varindex -> {A} | A for every var in context
-- it is important to note that the order in {A} is important
-- the state will also have an 'escaped' field with the variables that escaped


function scalar_replacement.run(module)
    print(require('pallene.print_ir')(module))
    for _, func in ipairs(module.functions) do
        local cmd = func.body
        local states = AEval(cmd)
        local count = 0
        ir.map_cmd(cmd,function(_cmd)
            count = count + 1
            if _cmd._tag == "ir.Cmd.GetArr" then
                --print(inspect(_cmd))
                local i = nil
                if _cmd.src_i._tag == 'ir.Value.LocalVar' then
                    i = states[count][_cmd.src_i.id].value
                    --get_val(_cmd.src_i.id)
                elseif _cmd.src_i._tag == 'ir.Value.Integer' then
                    i = _cmd.src_i.value
                end
                print(count,_cmd.src_arr.id,i)
                print(inspect( states[count]))
                print(inspect( states[count][_cmd.src_arr.id]))
                print(inspect( states[count][_cmd.src_arr.id][i]))
                local value = states[count][_cmd.src_arr.id][i]
                if  value then
                    if not contains_id(states[count].escaped,_cmd.src_arr.id) then
                        return ir.Cmd.Move(_cmd.loc,_cmd.dst,value)
                    end
                end
            end
        end)
        clean_new_table(cmd)
        -- clean gc
        -- clean unused local vars
    end
    print(require('pallene.print_ir')(module))
    return module, {}
end

return scalar_replacement
