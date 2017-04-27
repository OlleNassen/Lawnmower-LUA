#include "World.h"

World::World(sf::Vector2i mapSize)
{
	m_mapSize = mapSize;

	loadPlayers();

    loadTiles();
    
}

World::~World()
{
    for (auto& players : m_players)
    {
        delete players;
    }

    for (auto& tiles : m_tiles)
    {
        for (auto& tile : tiles)
        {
            delete tile;
        }
    }
}

void World::loadPlayers()
{
	Player* one = new Player();
	one->getSprite()->setColor(sf::Color::Cyan);

	Player* two = new Player();
	two->getSprite()->setColor(sf::Color::Red);

	m_players.push_back(one);
	m_players.push_back(two);
}

void World::loadTiles()
{
    for (int x = 0; x < 25; x++)
    {
        std::vector<Tile*>tiles;
        for (int y = 0; y < 20; y++)
        {
            tiles.push_back(new Tile);
        }
        m_tiles.push_back(tiles);
    }
}

void World::update()
{
	for (auto& players : m_players)
	{
		players->collision(m_mapSize);
		players->update();
	}
}

void World::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    for (const auto& tiles : m_tiles)
    {
        for (const auto& tile : tiles)
        {
            target.draw(*tile, states);
        }
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
