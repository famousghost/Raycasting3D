#pragma once
#include "LineSegment.h"

class LineIntersection
{
public:

    float getMeterT(LineSegment p_ray, LineSegment p_wall);

    float getMeterU(LineSegment p_ray, LineSegment p_wall);

    float getDenominator(LineSegment p_ray, LineSegment p_wall);

    float getTValue(LineSegment p_ray, LineSegment p_wall);

    float getUValue(LineSegment p_ray, LineSegment p_wall);
    sf::Vector2f findPointOnLine(LineSegment p_ray, float p_t);
};

