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
    m_sprite.setOrigin({ 32 / 2, 32 / 2 });
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
	m_sprite.setPosition(getPosition());
}

void Player::collision(sf::Vector2i mapSize)
{
	lua_getglobal(L, "collision");
	if (lua_isfunction(L, -1))
	{
		lua_pushnumber(L, mapSize.x);
		lua_pushnumber(L, mapSize.y);
		lua_pcall(L, 2, 0, 0);
	}
	else std::cout << "collision is not a function" << std::endl;
}

void Player::move(float delta, std::string verticalDir, std::string horizontalDir)
{
    if (verticalDir == "up")
    {
        if (horizontalDir == "left")
        {
            m_sprite.setRotation(225);
        }

        else if (horizontalDir == "right")
        {
            m_sprite.setRotation(315);
        }
        else
        {
            m_sprite.setRotation(270);
        }
    }
    else if (verticalDir == "down")
    {
        if (horizontalDir == "left")
        {
			m_sprite.setRotation(135);
        }
        else if (horizontalDir == "right")
        {
			m_sprite.setRotation(45);
        }
        else
        {
			m_sprite.setRotation(90);
        }
    }
    else if (horizontalDir == "left")
    {
        m_sprite.setRotation(180);
    }

    else if (horizontalDir == "right")
    {
        m_sprite.setRotation(0);
    }


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

sf::Sprite * Player::getSprite()
{
	return &m_sprite;
}

sf::Vector2f Player::getPosition() const
{
	sf::Vector2f position;
	lua_getglobal(L, "getPosition");
	if (lua_isfunction(L, -1))
	{
		lua_pcall(L, 0, 2, 0);
		position.x = lua_tonumber(L, -2);
		position.y = lua_tonumber(L, -1);
		lua_pop(L, 2);
	}
	else std::cout << "getPosition is not a function" << std::endl;

	return position;
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
