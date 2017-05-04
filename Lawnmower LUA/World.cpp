#include "World.h"

World::World(sf::Vector2i mapSize, std::shared_ptr<ResourceManager> resources)
{
	m_mapSize = mapSize;

	loadPlayers(4, resources);

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

void World::loadPlayers(int nrOfPlayers, std::shared_ptr<ResourceManager> resources)
{
	// Color of the four players
	sf::Color color[4] = 
	{ 
		sf::Color::Cyan,
		sf::Color::Red,	
		sf::Color::Green,
		sf::Color::Yellow
	};

	// Starting positions of the four players
	sf::Vector2f position[4] = 
	{ 
		sf::Vector2f(48, 48), 
		sf::Vector2f(752, 48),
		sf::Vector2f(752, 592), 
		sf::Vector2f(48, 592)
	};

	// Loading players
	for (int i = 0; i < nrOfPlayers; i++)
	{
		Player* player = new Player(resources->fonts[0], resources->lawnmowers[0]);
		player->getSprite()->setColor(color[i]);
		player->setPosition(position[i]);
		m_players.push_back(player);
	}
}

void World::loadTiles(std::shared_ptr<ResourceManager> resources)
{

    std::ifstream map(".\\Resources\\map.txt");

    unsigned int x = 0;
    unsigned int y = 0;

    std::vector<Tile*> tiles;
    while (!map.eof())
    {

        int tileNr;
        map >> tileNr;

        switch (tileNr)
        {
        case 0:
            tiles.push_back(new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Grass));
            //m_tiles[x][y] = new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Grass);
            break;

        case 1:
            tiles.push_back(new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Ground));
            //m_tiles[x][y] = new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Ground);
            break;

        case 2:
            tiles.push_back(new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Stone));
            //m_tiles[x][y] = new Tile(&resources->tiles, sf::Vector2i(x, y), Tile::Stone);
            break;
        }


        if (map.peek() == '\n')
        {
            x = 0;
            y++;
            m_tiles.push_back(tiles);
            tiles.clear();
        }
        else
        {
            x++;
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

		// Player - Player collision
		for (auto& otherPlayer : m_players)
		{
			if (player != otherPlayer)
			{
				sf::FloatRect intersection;
				if (player->getHitbox().intersects(otherPlayer->getHitbox(), intersection))
				{
					// Fix position in x
					if (intersection.width < intersection.height)
					{
						if (player->getPosition().x < intersection.left)
						{
							player->setPosition(sf::Vector2f(player->getPosition().x - intersection.width * 0.5f, player->getPosition().y));
							otherPlayer->setPosition(sf::Vector2f(otherPlayer->getPosition().x + intersection.width * 0.5f, otherPlayer->getPosition().y));
						}
						else
						{
							player->setPosition(sf::Vector2f(player->getPosition().x + intersection.width * 0.5f, player->getPosition().y));
							otherPlayer->setPosition(sf::Vector2f(otherPlayer->getPosition().x - intersection.width * 0.5f, otherPlayer->getPosition().y));
						}
					}
					// Fix position in y
					else
					{
						if (player->getPosition().y < intersection.top)
						{
							player->setPosition(sf::Vector2f(player->getPosition().x, player->getPosition().y - intersection.height * 0.5f));
							otherPlayer->setPosition(sf::Vector2f(otherPlayer->getPosition().x, otherPlayer->getPosition().y + intersection.height * 0.5f));
						}
						else
						{
							player->setPosition(sf::Vector2f(player->getPosition().x, player->getPosition().y + intersection.height * 0.5f));
							otherPlayer->setPosition(sf::Vector2f(otherPlayer->getPosition().x, otherPlayer->getPosition().y - intersection.height * 0.5f));
						}
					}
				}
			}
		}

		// Player - Tile collision
        for (auto& tiles : m_tiles)
        {
            for (auto& tile : tiles)
            {
				sf::FloatRect intersection;

				// Player - Stone Tile collision
				if (tile->getTileType() == Tile::Stone && tile->getHitbox().intersects(player->getHitbox(), intersection))
				{
					// Fix position in x
					if (intersection.width < intersection.height)
					{
						if (player->getPosition().x < intersection.left)
						{
							player->setPosition(sf::Vector2f(player->getPosition().x - intersection.width, player->getPosition().y));
						}
						else
						{
							player->setPosition(sf::Vector2f(player->getPosition().x + intersection.width, player->getPosition().y));
						}
					}
					// Fix position in y
					else
					{
						if (player->getPosition().y < intersection.top)
						{
							player->setPosition(sf::Vector2f(player->getPosition().x, player->getPosition().y - intersection.height));
						}
						else
						{
							player->setPosition(sf::Vector2f(player->getPosition().x, player->getPosition().y + intersection.height));
						}
					}
				}

				// Player - Grass Tile collision
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
