#include "Tile.h"

Tile::Tile(std::vector<sf::Texture>* textures, sf::Vector2i index, tileType type)
{
	// Initialize Lua
	L = luaL_newstate();
	luaL_openlibs(L);
	loadLuaScript();

	m_textures = textures;
	setTileType(type);

	// temporary
	m_sprite.setPosition(sf::Vector2f(32 * index.x + 16, 32 * index.y + 16));
	m_sprite.setOrigin(16, 16);
	m_sprite.setRotation((rand() % 3 > 2) ? 270 : ((rand() % 3 > 1) ? 180 : ((rand() % 3 > 0) ? 90 : 0)));
}

Tile::Tile(const Tile & other) { }

Tile::~Tile() { }

void Tile::update()
{
	checkIfCut();
}

void Tile::loadLuaScript()
{
	int error = luaL_dofile(L, "Scripts/tile.lua");
	if (error == 1)
	{
		std::cout << "Failed to load with message: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

void Tile::checkIfCut()
{
	tileType type;
	lua_getglobal(L, "getType");
	if (lua_isfunction(L, -1))
	{
		lua_pcall(L, 0, 1, 0);
		type = tileType(int(lua_tonumber(L, -1)));
		lua_pop(L, 1);
	}
	else std::cout << "getType is not a function" << std::endl;
	if (m_type != type)
	{
		setTileType(type);
	}
}

Tile::tileType Tile::getTileType() const { return m_type; }
void Tile::setTileType(tileType type) 
{
	m_type = type;

	lua_getglobal(L, "setType");
	if (lua_isfunction(L, -1))
	{
		lua_pushnumber(L, type);
		lua_pcall(L, 1, 0, 0);
	}
	else std::cout << "setType is not a function" << std::endl;

	// Setting new texture on sprite
	m_sprite.setTexture(m_textures->at(0));
}

sf::FloatRect Tile::getHitbox() const
{
    return m_sprite.getGlobalBounds();
}
