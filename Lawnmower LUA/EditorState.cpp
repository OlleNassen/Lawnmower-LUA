#include "EditorState.h"



EditorState::EditorState(sf::RenderWindow& window, std::shared_ptr<ResourceManager> resources)
    :State(window)
{
    m_resources = resources;
	m_pressed = false;
	type = Tile::Grass;

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) type = Tile::Grass;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) type = Tile::Ground;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) type = Tile::Stone;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_pressed)
		edit(sf::Mouse::getPosition(m_window));

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
		m_pressed = false;
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
            if (tile.getTexture() == &m_resources->tiles[0]) // Grass
            {
                out << 0;
            }

            else if (tile.getTexture() == &m_resources->tiles[1]) // Cut grass
            {
                out << 1;
            }

            else if (tile.getTexture() == &m_resources->tiles[2]) // Stone
            {
                out << 2;
            }
        }
        out << '\n';
    }
}

void EditorState::edit(sf::Vector2i position)
{
//	m_pressed = true;

	lua_getglobal(L, "setTile");
	if (lua_isfunction(L, -1))
	{
		// temp
		lua_pushnumber(L, position.x / 32);
		lua_pushnumber(L, position.y / 32);
		lua_pushnumber(L, type);
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