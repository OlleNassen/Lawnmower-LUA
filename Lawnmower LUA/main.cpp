#include "GameEngine.h"
#include <lua.hpp>

int main()
{

    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    luaL_dofile(L, ".\\Scripts\\printHelloWorld.lua");

    GameEngine game;

    game.run();

    return 0;
}
