#pragma once
#include "State.h"

class EditorState :public State
{
private:
    std::shared_ptr<ResourceManager> m_resources;

public:
    EditorState(sf::RenderWindow& window, std::shared_ptr<ResourceManager> resources);
    ~EditorState();

    void handleEvents() override;
    void handleInput() override;
    void update() override;
    void draw()const override;

    void pause() override;
    void resume() override;
};

