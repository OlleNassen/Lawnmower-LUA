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

	Tile(std::string texturePath, sf::Vector2i position, tileType type = Grass);
	Tile(const Tile& other);
	~Tile();

	bool loadTexture(std::string path);
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

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif