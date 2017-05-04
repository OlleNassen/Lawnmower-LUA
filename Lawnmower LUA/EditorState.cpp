#include "EditorState.h"



EditorState::EditorState(sf::RenderWindow& window, std::shared_ptr<ResourceManager> resources)
    :State(window)
{
    m_resources = resources;

	// Initialize Lua
	L = luaL_newstate();
	luaL_openlibs(L);
	loadLuaScript();

	m_tiles.resize(25);
	for (int i = 0; i < 25; i++)
		m_tiles[i].resize(20);

	loadGrid();

    saveToFile();
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
    for (const auto& tiles : m_tiles)
    {
        for (const auto& tile : tiles)
        {
            m_window.draw(tile);
        }
    }
}

void EditorState::pause()
{
}

void EditorState::resume()
{
}

void EditorState::saveToFile() const
{
    std::ofstream out(".\\Resources\\test.txt");

    for (const auto& tiles : m_tiles)
    {
        for (const auto& tile : tiles)
        {
            //out << 0;
        }
        out << '\n';
    }
}

void EditorState::changeSprite(int type, sf::Vector2i index)
{
	m_tiles[index.y][index.x].setTexture(m_resources->tiles[type]);
	m_tiles[index.y][index.x].setPosition(sf::Vector2f(32 * index.x + 16, 32 * index.y + 16));
	m_tiles[index.y][index.x].setOrigin(16, 16);
	m_tiles[index.y][index.x].setRotation((rand() % 3 > 2) ? 270 : ((rand() % 3 > 1) ? 180 : ((rand() % 3 > 0) ? 90 : 0)));
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
		for (int x = 0; x < 25; x++)
		{
			lua_pushnumber(L, x);
			lua_gettable(L, -2);
			if (lua_istable(L, -1))
			{
				for (int y = 0; y < 20; y++)
				{
					lua_pushnumber(L, y);
					lua_gettable(L, -2);
					changeSprite(lua_tonumber(L, -1), sf::Vector2i(x, y));
					lua_pop(L, 1);
				}
			}
			else std::cout << "grid is not a table" << std::endl;
			
			lua_pop(L, 1);
			std::cout << std::endl;
		}
	}
	else std::cout << "grid is not a table" << std::endl;
}