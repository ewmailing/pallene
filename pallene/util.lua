-- Copyright (c) 2020, The Pallene Developers
-- Pallene is licensed under the MIT license.
-- Please refer to the LICENSE and AUTHORS files for details
-- SPDX-License-Identifier: MIT

local util = {}

function util.abort(msg)
    io.stderr:write(msg, "\n")
    os.exit(1)
end

-- Barebones string-based template function for generating C/Lua code. Replaces $VAR and ${VAR}
-- placeholders in the `code` template by the corresponding strings in the `substs` table.
--
-- Don't call this function in tail-call position, wrap the call in parens if necessary. This way if
-- there is an error you will get an accurate line number in the stack trace instead of just
-- "(...tail calls...)"
function util.render(code, substs)
    local err
    local out = string.gsub(code, "%$({?)([A-Za-z_][A-Za-z_0-9]*)(}?)",
        function(a, k, b)
            if a == "{" and b == "" then
                err = "unmatched ${ in template"
                return ""
            end
            local v = substs[k]
            if not v then
                err = "missing template variable " .. k
                return ""
            elseif type(v) ~= "string" then
                err = "template variable is not a string " .. k
                return ""
            end
            if a == "" and b == "}" then
                v = v .. b
            end
            return v
        end)
    if err then
        error(err)
    end
    return out
end

--
-- Shell and filesystem stuff
--

function util.split_ext(file_name)
    local name, ext = string.match(file_name, "(.*)%.(.*)")
    return name, ext
end

function util.get_file_contents(file_name)
    local f, err = io.open(file_name, "r")
    if not f then
        return false, err
    end
    local s = f:read("a")
    f:close()
    if not s then
        return false, "unable to open file " .. file_name
    else
        return s
    end
end

function util.set_file_contents(file_name, contents)
    local f, err = io.open(file_name, "w")
    if not f then
        return false, err
    end
    f:write(contents)
    f:close()
    return true
end

-- Quotes a command-line argument according to POSIX shell syntax.
function util.shell_quote(str)
    return "'" .. string.gsub(str, "'", "'\\''") .. "'"
end

function util.execute(cmd)
    local ok = os.execute(cmd)
    if ok then
        return true
    else
        return false, "command failed: " .. cmd
    end
end

function util.outputs_of_execute(cmd)
    local out_file = os.tmpname()
    local err_file = os.tmpname()

    local redirected =
        cmd ..
        " > "  .. util.shell_quote(out_file) ..
        " 2> " .. util.shell_quote(err_file)

    local ok, err = util.execute(redirected)
    local out_content = assert(util.get_file_contents(out_file))
    local err_content = assert(util.get_file_contents(err_file))
    os.remove(out_file)
    os.remove(err_file)
    return ok, err, out_content, err_content
end

-- performs a deep copy of the table 'obj'

function util.copy(_obj)
    -- creates a closure to properly ignore the 'seen' parameter on root call
    local function _copy(obj,seen)
        -- Handle non-tables and previously-seen tables.
        if type(obj) ~= 'table' then return obj end
        if seen and seen[obj] then return seen[obj] end

        -- New table; mark it as seen an copy recursively.
        local s = seen or {}
        local res = {}
        s[obj] = res
        for k, v in next, obj do res[_copy(k, s)] = _copy(v, s) end
        return setmetatable(res, getmetatable(obj))
    end
    return _copy(_obj)
end


--
-- OOP
--

function util.Class()
    local cls = {}
    cls.__index = cls

    cls.new = function(...)
        local self = setmetatable({}, cls)
        self:init(...)
        return self
    end

    return cls
end

return util
