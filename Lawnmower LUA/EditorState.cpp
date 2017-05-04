#include "EditorState.h"



EditorState::EditorState(sf::RenderWindow& window, std::shared_ptr<ResourceManager> resources)
    :State(window)
{
    m_resources = resources;

	// Initialize Lua
	L = luaL_newstate();
	luaL_openlibs(L);
	loadLuaScript();

	loadGrid();
}


EditorState::~EditorState()
{

}

void EditorState::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();

        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_changeState = true;
                m_nextState = States::EXIT;
            }

    }
}

void EditorState::handleInput()
{
}

void EditorState::update()
{
}

void EditorState::draw() const
{
}

void EditorState::pause()
{
}

void EditorState::resume()
{
}

void EditorState::loadLuaScript()
{
	int error = luaL_dofile(L, "Scripts/editor.lua");
	if (error == 1)
	{
		std::cout << "Failed to load with message: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
}

void EditorState::loadGrid()
{
	lua_getglobal(L, "grid");
	if (lua_istable(L, -1))
	{
		lua_pushnumber(L, 1);
		lua_gettable(L, -2);
		if (lua_istable(L, -1))
		{
			lua_pushnumber(L, 1);
			lua_gettable(L, -2);
			std::cout << lua_tonumber(L, -1) << std::endl;
			lua_pop(L, 1);
		}	
		else
			std::cout << "grid is not a table" << std::endl;
		lua_pop(L, 1);
	}
	else std::cout << "grid is not a table" << std::endl;
}