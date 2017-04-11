#pragma once
#include "State.h"
#include <vector>
#include "Button.h"
#include "ResourceManager.h"
#include <memory>


class MenuState : public State
{
private:
    std::vector<Button> m_buttons;
    std::shared_ptr<ResourceManager> m_resources;
public:
    MenuState(sf::RenderWindow& window, std::shared_ptr<ResourceManager> resources);
    ~MenuState();

    void handleEvents() override;
    void handleInput() override;
    void update() override;
    void draw()const override;

    void pause() override;
    void resume() override;
};

