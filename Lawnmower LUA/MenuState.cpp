#include "MenuState.h"
#include "GameState.h"
#include "EditorState.h"

MenuState::MenuState(sf::RenderWindow& window, std::shared_ptr<ResourceManager> resources)
    :State(window)
{
    m_buttons.emplace_back(Button("PLAY",{ 400 - (300 / 2), 50 }, resources->fonts[0]));
    m_buttons.emplace_back(Button("LEVEL EDITOR", {400 - (300 / 2), 250}, resources->fonts[0]));
    m_buttons.emplace_back(Button("EXIT", {400 - (300 / 2), 450}, resources->fonts[0]));

    m_resources = resources;
}


MenuState::~MenuState()
{
}

void MenuState::handleEvents()
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

void MenuState::handleInput()
{
    for (auto& button : m_buttons)
    {
        if (button.onPress(&m_window))
        {
            if (button.getTitle() == "PLAY")
            {
                m_nextState = States::GAME;
                m_changeState = true;
            }
            else if (button.getTitle() == "LEVEL EDITOR")
            {
                m_nextState = States::EDITOR;
                m_changeState = true;
            }
            else if (button.getTitle() == "EXIT")
            {
                m_nextState = States::EXIT;
                m_changeState = true;
            }
        }
    }

}

void MenuState::update()
{
    
}

void MenuState::draw() const
{
    for (const auto& buttons : m_buttons)
    {
        m_window.draw(buttons);
    }
}

void MenuState::pause()
{
}

void MenuState::resume()
{
}