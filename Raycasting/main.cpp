#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include "GameWindow.h"
#include "Input.h"
#include "LightSimulation.h"
#include "Transformations.h"

int main()
{
    const float l_sideBarSize = 100.0f;
    const unsigned int l_windowWidth = 800;
    const unsigned int l_windowHeight = 400;
    std::string l_title = "Raycasting";
    LightSimulation l_lightSimulation;
    double l_rayLength = 1000000000.0;
    sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default);
    static double l_time = 0.1;
    l_lightSimulation.prepareScene();
    auto& l_ray = l_lightSimulation.getRay();
    float l_prevTime = 0.0f;
    float l_currentTime = 0.0f;
    sf::Clock clock;
    sf::RectangleShape rectangleShape;
    while (m_window.isOpen())
    {
        sf::Time l_elapsed = clock.getElapsedTime();
        l_prevTime = l_currentTime;
        l_currentTime = l_elapsed.asSeconds();
        float l_deltaTime = l_currentTime - l_prevTime;
        m_window.clear();
        Input::buttonsClick(m_window);
        Input::move(l_ray.m_origin, l_ray.normalizedDirection(), l_deltaTime);
        l_ray.m_origin.x = Transformations::clamp(l_ray.m_origin.x, l_windowWidth / 2 + 1, l_windowWidth - 1);
        l_ray.m_origin.y = Transformations::clamp(l_ray.m_origin.y, 1, l_windowHeight - 1);
        Input::rotate(l_ray.m_direction, l_deltaTime);
        l_lightSimulation.createRays();
        l_lightSimulation.increaseFov();
        l_lightSimulation.decreaseFov();
        auto l_rayDistances = l_lightSimulation.getDistances();

        int widthSize = l_windowWidth / l_rayDistances.size() / 2;
        for (int i = 0; i < l_rayDistances.size(); ++i)
        {
            double dist = l_rayDistances[i];
            double colorValue = Transformations::remap(dist, 0.0, l_windowHeight, 255.0, 0.0);
            double heightValue = Transformations::remap(dist, 0.0, 2000.0, l_windowHeight, 0.0);

            rectangleShape.setFillColor(sf::Color(255, 255, 255, colorValue));
            rectangleShape.setPosition(sf::Vector2f(widthSize * i, 0));
            rectangleShape.setSize(sf::Vector2f(widthSize, heightValue));

            m_window.draw(rectangleShape);
        }

        l_lightSimulation.drawElements(m_window);

        m_window.display();
    }

    return 0;
}