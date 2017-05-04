#include "World.h"

World::World(sf::Vector2i mapSize, std::shared_ptr<ResourceManager> resources)
{
	m_mapSize = mapSize;

	loadPlayers(resources);

    loadTiles(resources);
    
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

void World::loadPlayers(std::shared_ptr<ResourceManager> resources)
{
	Player* one = new Player(resources->fonts[0], resources->lawnmowers[0]);
	one->getSprite()->setColor(sf::Color::Cyan);

	Player* two = new Player(resources->fonts[0], resources->lawnmowers[0]);
	two->getSprite()->setColor(sf::Color::Red);

	m_players.push_back(one);
	m_players.push_back(two);
}

void World::loadTiles(std::shared_ptr<ResourceManager> resources)
{
    std::ifstream map(".\\map.txt");

    unsigned int x = 0;
    unsigned int y = 0;
    
    while (!map.eof())
    {
        std::vector<Tile*> tiles;

        int tileNr;
        map >> tileNr;

        switch (tileNr)
        {
        case 0:
            tiles.push_back(new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Grass));
            //m_tiles[x][y] = new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Grass);
            break;

        case 1:
            tiles.push_back(new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Grass));
            //m_tiles[x][y] = new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Ground);
            break;

        case 2:
            tiles.push_back(new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Grass));
            //m_tiles[x][y] = new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Stone);
            break;
        }

        if (map.peek() == '\n')
        {
            x++;
            y = 0;
            m_tiles.push_back(tiles);
            tiles.clear();
        }
        else
        {
            y++;
        }

    }
    /*
    for (int x = 0; x < 25; x++)
    {
        std::vector<Tile*>tiles;
        for (int y = 0; y < 20; y++)
        {
            tiles.push_back(new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Grass));
        }
        m_tiles.push_back(tiles);
    }
    */
}

void World::collision()
{
    for (auto& player : m_players)
    {
        for (auto& tiles : m_tiles)
        {
            for (auto& tile : tiles)
            {
                if (tile->getHitbox().contains(player->getPosition()) && tile->getTileType() == Tile::Grass)
                {
                    tile->setTileType(Tile::Ground);
					player->addPoint();
                }
            }
        }
    }
}

void World::update()
{
    collision();
	for (auto& players : m_players)
	{
		players->collision(m_mapSize);
		players->update();
	}

	for (const auto& tiles : m_tiles)
	{
		for (const auto& tile : tiles)
		{
			tile->update();
		}
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
