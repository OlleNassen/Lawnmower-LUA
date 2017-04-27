#pragma once

#include "Tile.h"
#include "Player.h"
#include <SFML\Graphics.hpp>
#include <vector>

class World: public sf::Drawable
{
private:
    std::vector<Tile> m_tiles;
    std::vector<Player> m_players;
public:
    World();
    virtual ~World();

    void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
};

