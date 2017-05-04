#pragma once
#include "State.h"
#include "lua.hpp"

class EditorState :public State
{
private:
    std::shared_ptr<ResourceManager> m_resources;
	std::vector<std::vector<sf::Sprite>> m_tiles;
	lua_State* L;

	void loadLuaScript();
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

