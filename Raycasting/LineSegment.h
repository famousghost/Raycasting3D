#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "Ray.h"

struct LineSegment
{
    LineSegment(sf::Vector2f p_startPoint, sf::Vector2f p_endPoint);
    LineSegment rayToLineSegment(const Ray & p_ray);
    LineSegment() = default;
    sf::Vector2f m_startPoint;
    sf::Vector2f m_endPoint;
};

