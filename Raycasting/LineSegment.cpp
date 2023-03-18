#include "LineSegment.h"

LineSegment::LineSegment(sf::Vector2f p_startPoint, sf::Vector2f p_endPoint)
    :m_startPoint(p_startPoint), m_endPoint(p_endPoint)
{}

LineSegment LineSegment::rayToLineSegment(const Ray& p_ray)
{
    return LineSegment(p_ray.m_origin, p_ray.m_origin + p_ray.m_direction);
}