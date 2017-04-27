#include "Player.h"

Player::Player()
{
	loadTexture("texture.png");
}

Player::Player(const Player & other) { }

Player::~Player() { }

bool Player::loadTexture(std::string path)
{
	if (!m_texture.loadFromFile(path))
		return false;

	m_sprite.setTexture(m_texture);
	return true;
}

void Player::update()
{

}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
