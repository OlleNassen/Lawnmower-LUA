#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>

struct ResourceManager
{
    std::vector<sf::Font> fonts;
    std::vector<sf::Texture> tiles;
    std::vector<sf::Texture> lawnmowers;

    ResourceManager()
    {
        sf::Font font;
        if (!font.loadFromFile(".\\Resources\\font.ttf"))
        {
            std::cout << "Couldn't load file";
        }
        fonts.push_back(font);
    
        sf::Texture grass;
        grass.loadFromFile(".\\Resources\\grass32x32.png");
        tiles.push_back(grass);

        sf::Texture cutGrass;
        cutGrass.loadFromFile(".\\Resources\\cut_grass32x32.png");
        tiles.push_back(cutGrass);

        sf::Texture lawnmower;
        lawnmower.loadFromFile(".\\Resources\\lawnmower32x32.png");
        lawnmowers.push_back(lawnmower);
    
    }


};

