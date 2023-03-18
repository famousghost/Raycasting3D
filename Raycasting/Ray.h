#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

struct Ray
{
    Ray(sf::Vector2f p_origin, sf::Vector2f p_direction);
    float len(sf::Vector2f p_vec) const;
    sf::Vector2f normalizedDirection() const;
    Ray() = default;
    sf::Vector2f m_origin;
    sf::Vector2f m_direction;
};

