#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include "lua.hpp"

class Player : public sf::Drawable, sf::Transformable
{
public:
	Player(sf::Font& font, sf::Texture& texture);
	Player(const Player& other);
	~Player();
	
	void update();
	void updatePosition();

	void addPoint();
	void collision(sf::Vector2i mapSize);
	void collisionWithTiles(std::vector<Tile>* tiles);
	void move(float delta, std::string horizontalDir, std::string verticalDir);

	sf::Sprite* getSprite();
	sf::Vector2f Player::getPosition() const;
	void Player::setPosition(sf::Vector2f position);
	sf::FloatRect getHitbox() const;
private:
	void loadLuaScript();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	lua_State* L;
	sf::Sprite m_sprite;
	sf::Text m_text;
};


#endif // !PLAYER_H
