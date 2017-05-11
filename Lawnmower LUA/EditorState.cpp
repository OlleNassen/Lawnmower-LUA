#include "EditorState.h"



EditorState::EditorState(sf::RenderWindow& window, std::shared_ptr<ResourceManager> resources)
    :State(window)
{
    m_resources = resources;
	m_type = Tile::Stone;
	m_type = Tile::Grass; m_textType.setString("Tile: Stone");

	// Create text
	m_textType.setFont(m_resources->fonts[0]);
	m_textType.setPosition(10, 640 - m_textType.getGlobalBounds().height - 20);

	m_textInfo.setFont(m_resources->fonts[0]);
	m_textInfo.setCharacterSize(15);
	m_textInfo.setString("Esq: Back\nS: Save\n1: Grass\n2: Ground\n3: Stone");
	m_textInfo.setPosition(5, 0);

	// Initialize Lua
	L = luaL_newstate();
	luaL_openlibs(L);
	loadLuaScript();

	m_tiles.resize(25);
	for (int i = 0; i < 25; i++)
		m_tiles[i].resize(20);

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { m_type = Tile::Grass; m_textType.setString("Tile: Grass"); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { m_type = Tile::Ground; m_textType.setString("Tile: Ground"); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { m_type = Tile::Stone; m_textType.setString("Tile: Stone"); }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		lua_getglobal(L, "saveToFile");
		if (lua_isfunction(L, -1))
		{
			lua_pcall(L, 0, 0, 0);
		}
		else std::cout << "saveTofile is not a function" << std::endl;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		edit(sf::Mouse::getPosition(m_window));
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
	m_window.draw(m_textType);
	m_window.draw(m_textInfo);
}

void EditorState::pause()
{
}

void EditorState::resume()
{
}

int EditorState::saveToFile(lua_State* L)
{
    std::ofstream out(".\\Resources\\map.lawn");

	lua_getglobal(L, "grid");
	if (lua_istable(L, -1))
	{
		for (int y = 0; y < 20; y++)
		{
			lua_pushnumber(L, y);
			lua_gettable(L, -2);
			if (lua_istable(L, -1))
			{
				for (int x = 0; x < 25; x++)
				{
					lua_pushnumber(L, x);
					lua_gettable(L, -2);
					out << lua_tointeger(L, -1);
					if (x != 24) out << ' ';
					lua_pop(L, 1);
				}
			}
			else std::cout << "grid is not a table" << std::endl;

			lua_pop(L, 1);
			out << '\n';
		}
	}
	else std::cout << "grid is not a table" << std::endl;

	return 0;
}

void EditorState::edit(sf::Vector2i position)
{
	lua_getglobal(L, "setTile");
	if (lua_isfunction(L, -1))
	{
		// temp
		lua_pushnumber(L, position.x / 32);
		lua_pushnumber(L, position.y / 32);
		lua_pushnumber(L, m_type);
		lua_pcall(L, 3, 0, 0);
		loadGrid();
	}
	else std::cout << "setTile is not a function" << std::endl;
}

void EditorState::changeSprite(int type, sf::Vector2i index)
{
	m_tiles[index.x][index.y].setTexture(m_resources->tiles[type]);
	m_tiles[index.x][index.y].setPosition(sf::Vector2f(32 * index.x + 16, 32 * index.y + 16));
	m_tiles[index.x][index.y].setOrigin(16, 16);
//	m_tiles[index.x][index.y].setRotation((rand() % 3 > 2) ? 270 : ((rand() % 3 > 1) ? 180 : ((rand() % 3 > 0) ? 90 : 0)));
}

void EditorState::loadLuaScript()
{
	int error = luaL_dofile(L, "Scripts/editor.lua");
	if (error == 1)
	{
		std::cout << "Failed to load with message: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}

	lua_pushcfunction(L, saveToFile);
	lua_setglobal(L, "save");
}

void EditorState::loadGrid()
{
	lua_getglobal(L, "grid");
	if (lua_istable(L, -1))
	{
		for (int y = 0; y < 20; y++)
		{
			lua_pushnumber(L, y);
			lua_gettable(L, -2);
			if (lua_istable(L, -1))
			{
				for (int x = 0; x < 25; x++)
				{
					lua_pushnumber(L, x);
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