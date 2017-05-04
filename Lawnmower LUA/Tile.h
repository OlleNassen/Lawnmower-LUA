#ifndef TILE_H
#define TILE_H
#include <SFML\Graphics.hpp>
#include <string>
#include "lua.hpp"
#include <iostream>

class Tile : public sf::Drawable
{
public:
	enum tileType 
	{
		Grass,
		Ground,
		Stone
	};

	Tile(std::vector<sf::Texture*>* textures, sf::Vector2i position, tileType type = Grass);
	Tile(const Tile& other);
	~Tile();

	void update();

	tileType getTileType() const;
	void setTileType(tileType type);

    sf::FloatRect getHitbox()const;

private:
	void checkIfCut();
	void loadLuaScript();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	tileType m_type;
	lua_State* L;

	std::vector<sf::Texture*>* m_textures;
	sf::Sprite m_sprite;
};

#endif