#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "lua.hpp"

class Player : public sf::Drawable, sf::Transformable
{
public:
	Player();
	Player(const Player& other);
	~Player();
	
	bool loadTexture(std::string path);
	void update();
	void updatePosition();

	void collision(sf::Vector2i mapSize);
	void move(float delta, std::string horizontalDir, std::string verticalDir);

	sf::Sprite* getSprite();
private:
	void loadLuaScript();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	lua_State* L;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};


#endif // !PLAYER_H
