#include "LightSimulation.h"
#include "Transformations.h"
#include "LineIntersection.h"
#include "Input.h"

std::array<sf::Vertex, 2> LightSimulation::createRayShape(const Ray& p_ray, float p_len)
{
    std::array<sf::Vertex, 2> l_rayShape =
    {
        sf::Vertex(p_ray.m_origin),
        sf::Vertex(p_ray.m_origin + p_ray.normalizedDirection() * static_cast<float>(p_len))
    };
    return l_rayShape;
}

std::vector<std::array<sf::Vertex, 2>> LightSimulation::createLinesShape(std::vector<LineSegment> p_lines)
{
    std::vector<std::array<sf::Vertex, 2>> l_lineShapes;
    for (auto& l_line : p_lines)
    {
        l_lineShapes.push_back(std::array<sf::Vertex, 2>{l_line.m_startPoint, l_line.m_endPoint});
    }
    return l_lineShapes;
}

void LightSimulation::increaseFov()
{
    if (Input::s_increaseFov)
    {
        m_fov++;
        m_fov = Transformations::clamp(m_fov, 2, 360);
    }
}

void LightSimulation::decreaseFov()
{
    if (Input::s_decreaseFov)
    {
        m_fov--;
        m_fov = Transformations::clamp(m_fov, 2, 360);
    }
}

double LightSimulation::getFov() const
{
    return m_fov;
}

void LightSimulation::prepareScene()
{
    sf::Vector2f l_center = sf::Vector2f(400.0f, 200.0f);
    m_rayLength = 1000.0;
    m_fov = 60;
    sf::Vector2f l_rayOrigin = sf::Vector2f(650.0f, 300.0f);
    sf::Vector2f l_rayDirection = sf::Vector2f(0.0f, -1.0f);

    m_lines =
    {
        LineSegment(sf::Vector2f(0.0f, 0.0f) + l_center, sf::Vector2f(250.0f,  0.0f) + l_center),
        LineSegment(sf::Vector2f(0.0f, 20.0f) + l_center, sf::Vector2f(250.0f,  20.0f) + l_center),
        LineSegment(sf::Vector2f(250.0f, 0.0f) + l_center, sf::Vector2f(250.0f,  20.0f) + l_center),
        LineSegment(sf::Vector2f(50.0f, -100.0f) + l_center, sf::Vector2f(300.0f, -100.0f) + l_center),
        LineSegment(sf::Vector2f(50.0f, -120.0f) + l_center, sf::Vector2f(300.0f, -120.0f) + l_center),
        LineSegment(sf::Vector2f(300.0f, -100.0f) + l_center, sf::Vector2f(300.0f, -120.0f) + l_center),
        LineSegment(sf::Vector2f(50.0f, -100.0f) + l_center, sf::Vector2f(50.0f, -120.0f) + l_center),
        LineSegment(sf::Vector2f(0.0f, -200.0) + l_center, sf::Vector2f(400.0f, -200.0f) + l_center),
        LineSegment(sf::Vector2f(100.0f, -100.0f) + l_center, sf::Vector2f(100.0f, 100.0f) + l_center),
        LineSegment(sf::Vector2f(120.0f, -100.0f) + l_center, sf::Vector2f(120.0f, 100.0f) + l_center),
        LineSegment(sf::Vector2f(100.0f, 100.0f) + l_center, sf::Vector2f(120.0f, 100.0f) + l_center),
        LineSegment(sf::Vector2f(400.0f, -200.0) + l_center, sf::Vector2f(400.0f, 200.0f) + l_center),
        LineSegment(sf::Vector2f(0.0f, -200.0) + l_center, sf::Vector2f(0.0f, 200.0f) + l_center),
        LineSegment(sf::Vector2f(0.0f, 200.0) + l_center, sf::Vector2f(400.0f, 200.0f) + l_center)
    };

    m_ray = Ray(l_rayOrigin, l_rayDirection * static_cast<float>(m_rayLength));
    m_lineShapes = createLinesShape(m_lines);
}

void LightSimulation::createRays()
{
    m_distances.clear();
    m_rayShapes.clear();
    if (Input::s_increaseFov)
    {
    }
    LineIntersection l_lineIntersection;
    Ray ray(m_ray.m_origin, m_ray.m_direction * static_cast<float>(m_rayLength));
    for (int i = -m_fov / 2; i < m_fov / 2; ++i)
    {
        ray.m_direction = Transformations::rotate(m_ray.m_direction, i);
        std::array<sf::Vertex, 2> l_rayShape = createRayShape(ray, m_rayLength);
        double l_minDistance = 10000000000.0;
        Ray l_currentRay;
        for (auto& l_line : m_lines)
        {
            auto l_t = l_lineIntersection.getTValue(Transformations::rayToLineSegment(ray), l_line);
            auto l_u = l_lineIntersection.getUValue(Transformations::rayToLineSegment(ray), l_line);
            if (l_t >= 0.0f && l_t <= 1.0f && l_u <= 1.0f && l_u >= 0.0f)
            {
                sf::Vector2f l_pointOnRay = l_lineIntersection.findPointOnLine(Transformations::rayToLineSegment(ray), l_t);
                double l_distance = Transformations::distance(ray.m_origin, l_pointOnRay);
                if (Input::s_fixedFov)
                {
                    l_distance *= Transformations::dot(ray.normalizedDirection(), m_ray.normalizedDirection());
                }
                if (l_minDistance > l_distance)
                {
                    l_rayShape = createRayShape(ray, l_distance);
                    l_currentRay = Ray(ray.m_origin, l_pointOnRay);
                    l_minDistance = l_distance;
                }
            }
        }
        m_rayShapes.push_back(l_rayShape);
        m_distances.push_back(l_minDistance);
    }
}

std::vector<double> LightSimulation::getDistances() const
{
    return m_distances;
}

void LightSimulation::drawElements(sf::RenderWindow& p_window)
{
    for (auto& ray : m_rayShapes)
    {
        p_window.draw(ray.data(), 2, sf::Lines);
    }
    for (auto& l_lineShape : m_lineShapes)
    {
        p_window.draw(l_lineShape.data(), 2, sf::Lines);
    }
}

Ray& LightSimulation::getRay()
{
    return m_ray;
}