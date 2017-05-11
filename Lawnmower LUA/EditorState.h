#pragma once
#include "State.h"
#include "lua.hpp"
#include "Tile.h"
#include <fstream>

class EditorState :public State
{
private:
    std::shared_ptr<ResourceManager> m_resources;
	std::vector<std::vector<sf::Sprite>> m_tiles;
	lua_State* L;
	Tile::tileType m_type;
	sf::Text m_textType;

	void edit(sf::Vector2i position);
	void changeSprite(int type, sf::Vector2i index);
	void loadLuaScript();
	void loadGrid();
public:
    EditorState(sf::RenderWindow& window, std::shared_ptr<ResourceManager> resources);
    ~EditorState();

    void handleEvents() override;
    void handleInput() override;
    void update() override;
    void draw()const override;

    void pause() override;
    void resume() override;

    static int saveToFile(lua_State* L);
};

