#include "Ray.h"
#include <cmath>

Ray::Ray(sf::Vector2f p_origin, sf::Vector2f p_direction)
    :m_origin(p_origin), m_direction(p_direction)
{}

float Ray::len(sf::Vector2f p_vec) const
{
    return std::sqrt(p_vec.x * p_vec.x + p_vec.y * p_vec.y);
}

sf::Vector2f Ray::normalizedDirection() const
{
    return m_direction / len(m_direction);
}