#include "GameEngine.h"
#include <lua.hpp>

int main()
{

    lua_State* L = luaL_newstate();

    luaL_openlibs;

    GameEngine game;

    game.run();

    

    return 0;
}
