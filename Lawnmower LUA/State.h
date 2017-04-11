#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include "ResourceManager.h"

enum class States
{
    NONE, MENU, GAME, EDITOR, EXIT
};

class State
{
protected:
    sf::RenderWindow& m_window;
    States m_nextState;
    bool m_changeState;

public:
    State(sf::RenderWindow& window):m_window(window), m_nextState(States::NONE), m_changeState(false){}
    virtual ~State() {}
    
    virtual void handleEvents() = 0;
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void draw()const = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    bool changeState()const
    {
        return m_changeState;
    }
    void resetState()
    {
        m_changeState = false;
    }

    virtual States nextState()const
    {
        return m_nextState;
    }
};