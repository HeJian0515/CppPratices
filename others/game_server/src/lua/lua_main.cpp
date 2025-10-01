#include <print>
#include <lua.hpp>

using namespace std;

extern "C" {
    // 第一步：声明 C 函数
    int call_add(lua_State* L) {
        int a = lua_tonumber(L, 1);
        int b = lua_tonumber(L, 2);
        lua_pop(L, 2);
        int result = a + b;
        lua_pushnumber(L, result);
        return 1;
    }
}


int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // 第二步：注册 C 函数到 Lua 环境中
    lua_register(L, "add", call_add);

    if (luaL_dofile(L, "main.lua") != LUA_OK) {
        println("Error running main.lua: {}", lua_tostring(L, -1));
        lua_close(L);
        exit(EXIT_FAILURE);
    }

    lua_close(L);
    return 0;
}