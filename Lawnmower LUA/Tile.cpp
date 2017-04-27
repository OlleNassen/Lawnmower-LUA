#include "Tile.h"

Tile::Tile() 
{
	m_type = Grass;
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

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}