#include "GameEngine.h"
#include "EditorState.h"


GameEngine::GameEngine()
    :m_window({ 800,640 }, "SFML with LUA")
{
    m_resources = std::make_shared<ResourceManager>();
    m_gameStates.push(std::make_unique<MenuState>(m_window, m_resources));
    m_window.setFramerateLimit(60);
}


GameEngine::~GameEngine()
{
}

void GameEngine::handleInput()
{
    m_gameStates.top()->handleInput();
}

void GameEngine::handleEvents()
{
    m_gameStates.top()->handleEvents();
}

void GameEngine::draw()
{
    m_gameStates.top()->draw();
}

void GameEngine::update()
{
    m_gameStates.top()->update();

    if (m_gameStates.top()->changeState())
    {

        switch (m_gameStates.top()->nextState())
        {
        case States::NONE:

            break;

        case States::EXIT:
            m_gameStates.pop();
            break;

        case States::GAME:
            m_gameStates.top()->resetState();
            m_gameStates.push(std::make_unique<GameState>(m_window, m_resources));
            break;

        case States::EDITOR:
            m_gameStates.top()->resetState();
            m_gameStates.push(std::make_unique<EditorState>(m_window, m_resources));
            break;
        }
    }

}

void GameEngine::run()
{
    while (m_window.isOpen())
    {
        handleInput();

        update();

        //::Spaghetti lösning:://

        if (m_gameStates.empty())
        {
            m_window.close();
            break;
        }

        handleEvents();

        m_window.clear();

        draw();

        m_window.display();

    }

}