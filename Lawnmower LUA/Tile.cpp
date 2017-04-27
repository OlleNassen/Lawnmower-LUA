#include "Tile.h"

Tile::Tile() 
{
	m_type = Grass;

	// Initialize Lua
	L = luaL_newstate();
	luaL_openlibs(L);
	loadLuaScript();
}

Tile::Tile(std::string texturePath, tileType type)
{
	m_type = type;
	loadTexture(texturePath);
}

Tile::Tile(const Tile & other) { }

Tile::~Tile() { }

bool Tile::loadTexture(std::string path)
{
	if (!m_texture.loadFromFile(path))
		return false;

	m_sprite.setTexture(m_texture);
	return true;
}

void Tile::update()
{

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

Tile::tileType Tile::getTileType() const { return m_type; }
void Tile::setTileType(tileType type) { m_type = type; }