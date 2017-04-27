#include "World.h"

World::World()
{
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
