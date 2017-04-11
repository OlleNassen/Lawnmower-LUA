#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include <iostream>

struct ResourceManager
{
    std::vector<sf::Font> fonts;

    ResourceManager()
    {
        sf::Font font;
        if (!font.loadFromFile(".\\Resources\\font.ttf"))
        {
            std::cout << "Couldn't load file";
        }
        fonts.push_back(font);
    }


};

