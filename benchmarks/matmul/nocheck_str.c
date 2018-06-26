/* This file was generated by the Titan compiler. Do not edit by hand */
/* Indentation and formatting courtesy of titan-compiler/pretty.lua */

#include <string.h>

#include "tcore.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "lapi.h"
#include "lfunc.h"
#include "lgc.h"
#include "lobject.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "lvm.h"

#include "math.h"

static Table * function_matmul_titan(
    lua_State * L,
    Table * x1 /* A */,
    Table * x2 /* B */
){
    lua_checkstack(L, 3);
    CClosure * x3 = clCvalue(s2v(L->ci->func));
    Table * x4 /* upvalue table */ = hvalue(&x3->upvalue[0]);
    TValue * x5 /* upvalue array */ = x4->array;
    (void)x5;
    {
        luaC_condGC(L, {
            StackValue* x6 = L->top;
            sethvalue(L, s2v(x6), x1); x6++;
            sethvalue(L, s2v(x6), x2); x6++;
            L->top = x6;
        }, {
            L->top -= 2;
        });
        Table * x7 = luaH_new(L);
        luaH_resizearray(L, x7, 0);
        TValue * x8 = x7->array;
        (void) x8;
        Table * x9 /* C */ = x7;
        lua_Integer x10 = luaH_getn(x1);
        lua_Integer x11 /* NI */ = x10;
        lua_Integer x12 = luaH_getn(x2);
        lua_Integer x13 /* NK */ = x12;
        lua_Unsigned x14 /* ui */ = ((lua_Unsigned)1) - 1;
        if (TITAN_UNLIKELY(x14 >= x2->sizearray)) {
            titan_renormalize_array(L, x2, x14, 5);
        }
        const TValue * x15 /* arrslot */ = &x2->array[x14];
        if (TITAN_UNLIKELY(!ttistable(x15))) {
            titan_runtime_array_type_error(L, 5, LUA_TTABLE, rawtt(x15));
        }
        Table * x16 = hvalue(x15);
        lua_Integer x17 = luaH_getn(x16);
        lua_Integer x18 /* NJ */ = x17;
        lua_Integer x19 /* start */ = 1;
        lua_Integer x20 /* finish */ = x11;
        lua_Integer x21 /* inc */ = 1;
        while ((x21 >= 0 ? x19 <= x20 : x19 >= x20)) {
            lua_Integer x22 /* i */ = x19;
            (void) x22;
            {
                luaC_condGC(L, {
                    StackValue* x23 = L->top;
                    sethvalue(L, s2v(x23), x1); x23++;
                    sethvalue(L, s2v(x23), x2); x23++;
                    sethvalue(L, s2v(x23), x9); x23++;
                    L->top = x23;
                }, {
                    L->top -= 3;
                });
                Table * x24 = luaH_new(L);
                luaH_resizearray(L, x24, 0);
                TValue * x25 = x24->array;
                (void) x25;
                Table * x26 /* line */ = x24;
                lua_Integer x27 /* start */ = 1;
                lua_Integer x28 /* finish */ = x18;
                lua_Integer x29 /* inc */ = 1;
                while ((x29 >= 0 ? x27 <= x28 : x27 >= x28)) {
                    lua_Integer x30 /* j */ = x27;
                    (void) x30;
                    {
                        lua_Unsigned x31 /* ui */ = ((lua_Unsigned)x30) - 1;
                        if (TITAN_UNLIKELY(x31 >= x26->sizearray)) {
                            titan_renormalize_array(L, x26, x31, 9);
                        }
                        TValue * x32 /* slot */ = &x26->array[x31];
                        setfltvalue(x32, 0x0p+0 /*0.000000*/);
                    }
                    x27 = intop(+, x27, x29);
                }
                lua_Unsigned x33 /* ui */ = ((lua_Unsigned)x22) - 1;
                if (TITAN_UNLIKELY(x33 >= x9->sizearray)) {
                    titan_renormalize_array(L, x9, x33, 11);
                }
                TValue * x34 /* slot */ = &x9->array[x33];
                sethvalue(L, x34, x26);
                if (isblack(obj2gco(x9)) && iswhite(obj2gco(x26))) {
                    luaC_barrierback_(L, obj2gco(x9));
                }
            }
            x19 = intop(+, x19, x21);
        }
        lua_Integer x35 /* start */ = 1;
        lua_Integer x36 /* finish */ = x13;
        lua_Integer x37 /* inc */ = 1;
        while ((x37 >= 0 ? x35 <= x36 : x35 >= x36)) {
            lua_Integer x38 /* k */ = x35;
            (void) x38;
            {
                lua_Unsigned x39 /* ui */ = ((lua_Unsigned)x38) - 1;
                if (TITAN_UNLIKELY(x39 >= x2->sizearray)) {
                    titan_renormalize_array(L, x2, x39, 14);
                }
                const TValue * x40 /* arrslot */ = &x2->array[x39];
                if (TITAN_UNLIKELY(!ttistable(x40))) {
                    titan_runtime_array_type_error(L, 14, LUA_TTABLE, rawtt(x40));
                }
                Table * x41 = hvalue(x40);
                Table * x42 /* Bk */ = x41;
                lua_Integer x43 /* start */ = 1;
                lua_Integer x44 /* finish */ = x11;
                lua_Integer x45 /* inc */ = 1;
                while ((x45 >= 0 ? x43 <= x44 : x43 >= x44)) {
                    lua_Integer x46 /* i */ = x43;
                    (void) x46;
                    {
                        lua_Unsigned x47 /* ui */ = ((lua_Unsigned)x46) - 1;
                        if (TITAN_UNLIKELY(x47 >= x1->sizearray)) {
                            titan_renormalize_array(L, x1, x47, 16);
                        }
                        const TValue * x48 /* arrslot */ = &x1->array[x47];
                        if (TITAN_UNLIKELY(!ttistable(x48))) {
                            titan_runtime_array_type_error(L, 16, LUA_TTABLE, rawtt(x48));
                        }
                        Table * x49 = hvalue(x48);
                        lua_Unsigned x50 /* ui */ = ((lua_Unsigned)x38) - 1;
                        if (TITAN_UNLIKELY(x50 >= x49->sizearray)) {
                            titan_renormalize_array(L, x49, x50, 16);
                        }
                        const TValue * x51 /* arrslot */ = &x49->array[x50];
                        if (TITAN_UNLIKELY(!ttisfloat(x51))) {
                            titan_runtime_array_type_error(L, 16, LUA_TNUMFLT, rawtt(x51));
                        }
                        lua_Number x52 = fltvalue(x51);
                        lua_Number x53 /* Aik */ = x52;
                        lua_Unsigned x54 /* ui */ = ((lua_Unsigned)x46) - 1;
                        if (TITAN_UNLIKELY(x54 >= x9->sizearray)) {
                            titan_renormalize_array(L, x9, x54, 17);
                        }
                        const TValue * x55 /* arrslot */ = &x9->array[x54];
                        if (TITAN_UNLIKELY(!ttistable(x55))) {
                            titan_runtime_array_type_error(L, 17, LUA_TTABLE, rawtt(x55));
                        }
                        Table * x56 = hvalue(x55);
                        Table * x57 /* Ci */ = x56;
                        lua_Integer x58 /* start */ = 1;
                        lua_Integer x59 /* finish */ = x18;
                        lua_Integer x60 /* inc */ = 1;
                        TValue *x57array = x57->array;
                        TValue *x42array = x42->array;
                        while ((x60 >= 0 ? x58 <= x59 : x58 >= x59)) {
                            lua_Integer x61 /* j */ = x58;
                            (void) x61;
                            {
                                const TValue * x63 /* arrslot */ = x57array;
                                lua_Number x64 = fltvalue(x63);
                                const TValue * x66 /* arrslot */ = x42array;
                                lua_Number x67 = fltvalue(x66);
                                lua_Number x68 = x53 * x67;
                                lua_Number x69 = x64 + x68;
                                chgfltvalue((TValue *)x63, x69);
                            }
                            x58 = intop(+, x58, x60);
                            x57array = x57array + 1;
                            x42array = x42array + 1;
                        }
                    }
                    x43 = intop(+, x43, x45);
                }
            }
            x35 = intop(+, x35, x37);
        }
        return x9;
    }
}

static int function_matmul_lua(lua_State *L)
{
    lua_checkstack(L, 1);
    CClosure * x1 = clCvalue(s2v(L->ci->func));
    Table * x2 /* upvalue table */ = hvalue(&x1->upvalue[0]);
    TValue * x3 /* upvalue array */ = x2->array;
    (void)x3;
    StackValue* x4 = L->ci->func;
    int x5 /* nargs */ = cast_int(L->top - (x4 + 1));
    if (TITAN_UNLIKELY(x5 != 2)) {
        titan_runtime_arity_error(L, 2, x5);
    }
    TValue* x6 = s2v(x4 + 1);
    if (TITAN_UNLIKELY(!ttistable(x6))) {
        titan_runtime_argument_type_error(L, "A", 1, LUA_TTABLE, x6);
    }
    TValue* x7 = s2v(x4 + 2);
    if (TITAN_UNLIKELY(!ttistable(x7))) {
        titan_runtime_argument_type_error(L, "B", 1, LUA_TTABLE, x7);
    }
    Table * x8 = hvalue(s2v(x4 + 1));
    Table * x9 = hvalue(s2v(x4 + 2));
    Table * x10 /* ret */ = function_matmul_titan(L, x8, x9);
    sethvalue(L, s2v(L->top), x10);
    api_incr_top(L);
    return 1;
}

int luaopen_benchmarks_matmul_nocheck_str(lua_State *L)
{
    lua_checkstack(L, 4);
    /* Allocate upvalue table */
    /* ---------------------- */
    Table * x1 = luaH_new(L);
    luaH_resizearray(L, x1, 3);
    TValue * x2 = x1->array;
    /* Initialize upvalues */
    /* ------------------- */
    TString * x3 = luaS_new(L, "__index");
    setsvalue(L,  &x2[0] , x3);
    if (isblack(obj2gco(x1)) && iswhite(obj2gco(x3))) {
        luaC_barrierback_(L, obj2gco(x1));
    }
    TString * x4 = luaS_new(L, "__metatable");
    setsvalue(L,  &x2[1] , x4);
    if (isblack(obj2gco(x1)) && iswhite(obj2gco(x4))) {
        luaC_barrierback_(L, obj2gco(x1));
    }
    /* matmul */
    CClosure* x5 = luaF_newCclosure(L, 1);
    x5->f = function_matmul_lua;
    sethvalue(L, &x5->upvalue[0], x1);
    TValue x6; setclCvalue(L, &x6, x5);
    setobj(L,  &x2[2] , &x6);
    if (iscollectable(&x6) && isblack(obj2gco(x1)) && iswhite(gcvalue(&x6))) {
        luaC_barrierback_(L, obj2gco(x1));
    }
    /* Create exports table */
    /* -------------------- */
    StackValue* x7 = L->top;
    sethvalue(L, s2v(x7), x1); x7++;
    L->top = x7;
    lua_createtable(L, 0, 1);
    lua_pushstring(L, "matmul");
    setobj(L, s2v(L->top),  &x2[2] ); api_incr_top(L);
    lua_settable(L, -3);
    return 1;
}

