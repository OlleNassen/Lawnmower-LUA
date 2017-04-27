#include "Player.h"

Player::Player()
{
	loadTexture("texture.png");

	// Initialize Lua
	L = luaL_newstate();
	luaL_openlibs(L);
	loadLuaScript();
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


	// Reload file
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		loadLuaScript();
}

void Player::loadLuaScript()
{
	int error = luaL_dofile(L, "Scripts/player.lua");
	if (error == 1)
	{
		std::cout << "Failed to load with message: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
