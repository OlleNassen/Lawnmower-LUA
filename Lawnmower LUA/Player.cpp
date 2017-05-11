#include "Player.h"

Player::Player(sf::Font& font, sf::Texture& texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setOrigin({ 32 / 2, 32 / 2 });

	// Setting text
	m_text.setFont(font);
	m_text.setCharacterSize(15.f);
	m_text.setOrigin({ m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2 });

	// Initialize Lua
	L = luaL_newstate();
	luaL_openlibs(L);
	loadLuaScript();

    m_text.setOutlineThickness(2.5f);
    m_text.setOutlineColor(sf::Color::Black);

}

Player::Player(const Player & other) { }

Player::~Player() { }

void Player::update()
{
	updatePosition();

	// Reload file
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		loadLuaScript();
}

void Player::updatePosition()
{
	sf::Vector2f pos = getPosition();

	m_sprite.setPosition(pos);
	m_text.setPosition(pos);
}

void Player::addPoint()
{
	lua_getglobal(L, "score");
	if (lua_isinteger(L, -1))
	{
		// Adding one score
		int score = lua_tointeger(L, -1) + 1;

		// Pushing to lua
		lua_pushinteger(L, score);
		lua_setglobal(L, "score");
		lua_pcall(L, 1, 0, 0);

		// Chaning text string
		m_text.setString(std::to_string(score));
		m_text.setOrigin({ m_text.getGlobalBounds().width / 2 + m_text.getOutlineThickness() - 5 , 25 + m_text.getGlobalBounds().height / 2 + m_text.getOutlineThickness() });
	}
	else std::cout << "Score is not an integer in lua." << std::endl;
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

void Player::collisionWithTiles(std::vector<std::vector<Tile*>>* tiles)
{
	bool isGrass = 0;
	lua_getglobal(L, "collisionWithTile");
	if (lua_isfunction(L, -1))
	{
		for (auto& tilesX : *tiles)
		{
			for (auto& tile : tilesX)
			{
				sf::FloatRect hitbox = tile->getHitbox();
				lua_pushnumber(L, (hitbox.left + hitbox.width / 2));
				lua_pushnumber(L, (hitbox.top + hitbox.height / 2));
				lua_pushnumber(L, hitbox.width);
				lua_pushnumber(L, static_cast<int>(tile->getTileType()));
				lua_pcall(L, 4, 1, 0);

				isGrass = false;
				isGrass = lua_toboolean(L, -1);
				if (isGrass)
					tile->setTileType(Tile::Ground);
			}
		}
	}
	else std::cout << "collisionWithTile is not a function" << std::endl;
}

void Player::collisionWithPlayer(Player* otherPlayer)
{
	lua_getglobal(L, "collisionWithPlayer");
	if (lua_isfunction(L, -1))
	{
		lua_pushnumber(L, otherPlayer->getPosition().x);
		lua_pushnumber(L, otherPlayer->getPosition().y);
		lua_pushnumber(L, otherPlayer->getHitbox().width);
		lua_pcall(L, 3, 3, 0);
		
		if (lua_toboolean(L, -3))
		{
			otherPlayer->setPosition(sf::Vector2f(otherPlayer->getPosition().x - lua_tonumber(L, -2), otherPlayer->getPosition().y - lua_tonumber(L, -1)));
		}
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

void Player::setPosition(sf::Vector2f position)
{
	lua_getglobal(L, "setPosition");
	if (lua_isfunction(L, -1))
	{
		lua_pushnumber(L, position.x);
		lua_pushnumber(L, position.y);
		lua_pcall(L, 2, 0, 0);
	}
	else std::cout << "setPosition is not a function" << std::endl;

	updatePosition();
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
	target.draw(m_text, states);
}

sf::FloatRect Player::getHitbox() const
{
	return m_sprite.getGlobalBounds();
}
