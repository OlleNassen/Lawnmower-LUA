#pragma once
#include <memory>
#include "MenuState.h"
#include "GameState.h"
#include <stack>
#include "ResourceManager.h"

class GameEngine
{

    sf::RenderWindow m_window;
    std::stack<std::unique_ptr<State>> m_gameStates;
    std::shared_ptr<ResourceManager> m_resources;

public:
    GameEngine();
    virtual ~GameEngine();

    void run();


private:
    void handleInput();
    void handleEvents();
    void draw();
    void update();
};

