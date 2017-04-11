#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

class Button : public sf::Drawable, public sf::Transformable
{
private:
    sf::RectangleShape m_box;
    sf::Text m_text;

public:
    Button(const std::string& text, const sf::Vector2f& position, sf::Font& font)
    {
        m_box.setSize({ 300, 100 });
        m_box.setPosition(position);
        m_box.setFillColor(sf::Color::Yellow);
        //m_box.setOutlineThickness(5); // Messes up hitbox a small bit

        m_text.setFont(font);
        m_text.setString(text);

        sf::Vector2f buttonPos = position;

        //Is Y position really correct?
        sf::Vector2f textPos((m_box.getGlobalBounds().width / 2) - (m_text.getGlobalBounds().width / 2), (m_box.getGlobalBounds().height / 2) - (m_text.getGlobalBounds().height / 2));

        sf::Vector2f correctTextPos = textPos + buttonPos;

        m_text.setPosition(correctTextPos);
        m_text.setCharacterSize(30);
        m_text.setFillColor(sf::Color::Black);
    }

    virtual ~Button()
    {

    }

    void draw(sf::RenderTarget& target, sf::RenderStates states)const override
    {
        target.draw(m_box, states);
        target.draw(m_text, states);
    }

    sf::Vector2f getSize()const
    {
        return m_box.getSize();
    }

    bool onPress(sf::RenderWindow* window)
    {
        sf::IntRect rect(m_box.getPosition().x, m_box.getPosition().y, m_box.getGlobalBounds().width, m_box.getGlobalBounds().height);

        if (rect.contains(sf::Mouse::getPosition(*window)) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            return true;
        }

        else if (rect.contains(sf::Mouse::getPosition(*window)))
        {
            m_box.setFillColor(sf::Color::Red);
        }

        else
        {
            m_box.setFillColor(sf::Color::Yellow);
        }

        return false;
    }

    std::string getTitle()const
    {
        return m_text.getString();
    }
};