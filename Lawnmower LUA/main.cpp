#include "GameEngine.h"
#include <lua.hpp>

int main()
{

    std::cout << "Olle";

    lua_State* L = luaL_newstate();

    luaL_openlibs;

    std::cout << "Github Test";

    GameEngine game;

    game.run();

    

    return 0;
}
