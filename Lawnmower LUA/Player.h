#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>

class Player : public sf::Drawable
{
public:
	Player();
	Player(const Player& other);
	~Player();
	
	bool loadTexture(std::string path);
	void update();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};


#endif // !PLAYER_H
