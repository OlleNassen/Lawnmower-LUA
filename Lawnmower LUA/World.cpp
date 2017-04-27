#include "World.h"

World::World(sf::Vector2i mapSize)
{
	m_mapSize = mapSize;

	m_players.push_back(new Player());
}

World::~World()
{
    for (auto& players : m_players)
    {
        delete players;
    }
}

void World::update()
{
	for (auto& players : m_players)
	{
		players->update();
		players->collision(m_mapSize);
	}
}

void World::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    for (const auto& tiles : m_tiles)
    {
        target.draw(tiles, states);
    }

    for (const auto& players : m_players)
    {
        target.draw(*players, states);
    }
}

void World::movePlayer(int player, float deltaTime, const std::string& verticalDir, const std::string & horizontalDir)
{
    m_players[player]->move(deltaTime, verticalDir, horizontalDir);
}
