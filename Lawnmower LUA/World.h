#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class World: public sf::Drawable
{
private:
    std::vector<Tile> m_tiles;
public:
    World();
    virtual ~World();
};

