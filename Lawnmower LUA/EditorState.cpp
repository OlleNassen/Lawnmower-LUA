#include "EditorState.h"



EditorState::EditorState(sf::RenderWindow& window, std::shared_ptr<ResourceManager> resources)
    :State(window)
{
    m_resources = resources;
}


EditorState::~EditorState()
{
}

void EditorState::handleEvents()
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

    }
}

void EditorState::handleInput()
{
}

void EditorState::update()
{
}

void EditorState::draw() const
{
}

void EditorState::pause()
{
}

void EditorState::resume()
{
}