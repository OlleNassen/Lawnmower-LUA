#ifndef TILE_H
#define TILE_H
#include <SFML\Graphics.hpp>
#include <string>

class Tile : public sf::Drawable
{
public:
	enum tileType 
	{
		Grass,
		Ground,
		Stone
	};

	Tile();
	Tile(std::string texturePath, tileType type = Grass);
	Tile(const Tile& other);
	~Tile();

	bool loadTexture(std::string path);
	void update();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	tileType m_type;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif