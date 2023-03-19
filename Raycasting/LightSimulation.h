#pragma once
#include <vector>
#include <array>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "LineSegment.h"

class LightSimulation
{
public:
    std::array<sf::Vertex, 2> createRayShape(const Ray& p_ray, float p_len);

    std::vector<std::array<sf::Vertex, 2>> createLinesShape(std::vector<LineSegment> p_lines);

    void increaseFov();

    void decreaseFov();

    double getFov() const;

    void prepareScene();

    void createRays();

    std::vector<double> getDistances() const;

    void drawElements(sf::RenderWindow& p_window);

    Ray& getRay();

private:
    Ray m_ray;
    std::vector<LineSegment> m_lines;
    std::vector<double> m_distances;
    std::vector< std::array < sf::Vertex, 2>> m_rayShapes;
    std::vector<std::array<sf::Vertex, 2>> m_lineShapes;
    int m_fov;
    double m_rayLength;
};
