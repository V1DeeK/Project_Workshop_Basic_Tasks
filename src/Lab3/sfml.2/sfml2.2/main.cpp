#include <SFML/Graphics.hpp>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Polar Rose",
        sf::State::Windowed, settings);
    
    // Формула: r = a * sin(n * angle), где n - количество лепестков
    sf::ConvexShape rose;
    const int pointCount = 500;
    rose.setPointCount(pointCount);
    const int petals = 20;
    const float maxRadius = 200.0f;
    for (int i = 0; i < pointCount; ++i)
    {
        float angle = 2.0f * static_cast<float>(M_PI) * i / static_cast<float>(pointCount);
        // Формула: r = maxRadius * sin(petals * angle)
        float radius = maxRadius * std::abs(std::sin(petals * angle));
        sf::Vector2f point = {
            radius * std::cos(angle),  // X координата точки
            radius * std::sin(angle)   // Y координата точки
        };
        rose.setPoint(i, point);
    }
    rose.setFillColor(sf::Color(0xFF, 0x09, 0x80));
    float time = 0.0f;
    float centerX = 400.0f;  // Центр окна по X (800/2)
    float centerY = 300.0f;  // Центр окна по Y (600/2)
    const float orbitRadius = 160.0f;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        
        time += 0.02f;
        
        // Вычисляем новую позицию розы по окружности
        // orbitRadius - радиус окружности, по которой движется роза
        // time - угол, который увеличивается со временем
        // std::cos(time) и std::sin(time) - координаты точки на окружности
        // centerX, centerY - центр окна (точка, вокруг которой движется роза)
        float x = centerX + orbitRadius * std::cos(time);
        float y = centerY + orbitRadius * std::sin(time);
        rose.setPosition({x, y});
        window.clear(sf::Color::White);
        window.draw(rose);
        window.display();
    }
    return 0;
}

