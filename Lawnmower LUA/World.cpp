#include "World.h"



World::World()
{
}


World::~World()
{
}

void World::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    for (const auto& tiles : m_tiles)
    {
        target.draw(tiles, states);
    }
}
