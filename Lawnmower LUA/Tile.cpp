#include "Tile.h"

Tile::Tile(std::string texturePath, sf::Vector2i index, tileType type)
{
	m_type = type;
	loadTexture(texturePath);

	// temporary
	m_sprite.setPosition(sf::Vector2f(32 * index.x, 32 * index.y));
	m_sprite.setOrigin(16, 16);
	int random = rand() % 4 + 1;
	switch (random)
	{ 
		case 1: m_sprite.setRotation(90); break;
		case 2: m_sprite.setRotation(180); break;
		case 3: m_sprite.setRotation(270); break;
		case 4: m_sprite.setRotation(0); break;
	}

	// Initialize Lua
	L = luaL_newstate();
	luaL_openlibs(L);
	loadLuaScript();
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