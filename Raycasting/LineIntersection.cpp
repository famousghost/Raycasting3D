#include "LineIntersection.h"
#include <iostream>

float LineIntersection::getMeterT(LineSegment p_ray, LineSegment p_wall)
{
    return (p_ray.m_startPoint.x - p_wall.m_startPoint.x)
        * (p_wall.m_startPoint.y - p_wall.m_endPoint.y)
        - (p_ray.m_startPoint.y - p_wall.m_startPoint.y)
        * (p_wall.m_startPoint.x - p_wall.m_endPoint.x);
}

float LineIntersection::getMeterU(LineSegment p_ray, LineSegment p_wall)
{
    return (p_ray.m_startPoint.x - p_ray.m_endPoint.x)
        * (p_ray.m_startPoint.y - p_wall.m_startPoint.y)
        - (p_ray.m_startPoint.y - p_ray.m_endPoint.y)
        * (p_ray.m_startPoint.x - p_wall.m_startPoint.x);
}

float LineIntersection::getDenominator(LineSegment p_ray, LineSegment p_wall)
{
    return (p_ray.m_startPoint.x - p_ray.m_endPoint.x)
        * (p_wall.m_startPoint.y - p_wall.m_endPoint.y)
        - (p_ray.m_startPoint.y - p_ray.m_endPoint.y)
        * (p_wall.m_startPoint.x - p_wall.m_endPoint.x);
}

float LineIntersection::getTValue(LineSegment p_ray, LineSegment p_wall)
{
    if (getDenominator(p_ray, p_wall) == 0)
    {
        return -1;
    }
    return getMeterT(p_ray, p_wall) / getDenominator(p_ray, p_wall);
}

float LineIntersection::getUValue(LineSegment p_ray, LineSegment p_wall)
{
    if (getDenominator(p_ray, p_wall) == 0)
    {
        return -1;
    }
    return -getMeterU(p_ray, p_wall) / getDenominator(p_ray, p_wall);
}

sf::Vector2f LineIntersection::findPointOnLine(LineSegment p_ray, float p_t)
{
    return sf::Vector2f(p_ray.m_startPoint.x + p_t
        * (p_ray.m_endPoint.x - p_ray.m_startPoint.x),
        p_ray.m_startPoint.y + p_t
        * (p_ray.m_endPoint.y - p_ray.m_startPoint.y));
}