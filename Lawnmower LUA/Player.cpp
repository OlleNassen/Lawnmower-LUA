#include "Player.h"

Player::Player()
{
	loadTexture(".\\Resources\\lawnmower32x32.png");

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
	updatePosition();

	// Reload file
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		loadLuaScript();
}

void Player::updatePosition()
{
	lua_getglobal(L, "getPosition");
	if (lua_isfunction(L, -1))
	{
		lua_pcall(L, 0, 2, 0);
		m_sprite.setPosition(lua_tonumber(L, -1), lua_tonumber(L, -2));
		lua_pop(L, 2);
	}
	else std::cout << "getPosition is not a function" << std::endl;
}

void Player::move(float delta, std::string verticalDir, std::string horizontalDir)
{
	lua_getglobal(L, "move");
	if (lua_isfunction(L, -1))
	{
		lua_pushnumber(L, delta);
		lua_pushstring(L, verticalDir.c_str());
		lua_pushstring(L, horizontalDir.c_str());
		lua_pcall(L, 3, 0, 0);
	}
	else std::cout << "move is not a function" << std::endl;
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
