#include "GameState.h"
#include "MenuState.h"


GameState::GameState(sf::RenderWindow& window, std::shared_ptr<ResourceManager> resources)
    :State(window)
{
    m_resources = resources;
}


GameState::~GameState()
{
}

void GameState::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();

        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_changeState = true;
                m_nextState = States::EXIT;
            }
		// hej
    }
}

void GameState::handleInput()
{
}

void GameState::update()
{
}

void GameState::draw() const
{
}

void GameState::pause()
{
}

void GameState::resume()
{
}