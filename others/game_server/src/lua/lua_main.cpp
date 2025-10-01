#include <print>
#include <lua.hpp>

extern "C" {

}

using namespace std;

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, "main.lua") != LUA_OK) {
        println("Error running main.lua: {}", lua_tostring(L, -1));
        lua_close(L);
        exit(EXIT_FAILURE);
    }

    lua_close(L);
    return 0;
}