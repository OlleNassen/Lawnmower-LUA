#include "GameState.h"
#include "MenuState.h"


GameState::GameState(sf::RenderWindow& window, std::shared_ptr<ResourceManager> resources)
    :State(window), m_world(sf::Vector2i(window.getSize()), resources)
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
	std::string horDir[4] = { "", "", "", "" };
	std::string verDir[4] = { "", "", "", "" };

	// Player One
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) verDir[0] = "up";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) verDir[0] = "down";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) horDir[0] = "left";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) horDir[0] = "right";

	// Player Two
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) verDir[1] = "up";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) verDir[1] = "down";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) horDir[1] = "left";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) horDir[1] = "right";

	// Player Three
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) verDir[2] = "up";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) verDir[2] = "down";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) horDir[2] = "left";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) horDir[2] = "right";

	// Player Four
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8)) verDir[3] = "up";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) verDir[3] = "down";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) horDir[3] = "left";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6)) horDir[3] = "right";

	// Moving players
	float delta = 1.f;
	int nrOfPlayers = 4;
	for (int i = 0; i < nrOfPlayers; i++)
	{
		if (!horDir[i].empty() || !verDir[i].empty())
			m_world.movePlayer(i, delta, verDir[i], horDir[i]);
	}
}

void GameState::update()
{
    m_world.update();
}

void GameState::draw() const
{
    m_window.draw(m_world);
}

void GameState::pause()
{
}

void GameState::resume()
{
}