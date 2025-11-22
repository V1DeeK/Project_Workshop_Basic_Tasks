#include <SFML/Graphics.hpp>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main()
{
    sf::ContextSettings settings;
    // antiAliasingLevel - уровень сглаживания краев фигур
    // Antialiasing - техника сглаживания краев за счет рисования полупрозрачных пикселей
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Moving Circle",
        sf::State::Windowed, settings);
    sf::ConvexShape circle;
    const int pointCount = 100;
    circle.setPointCount(pointCount);
    const float radius = 100.0f;
    for (int i = 0; i < pointCount; ++i)
    {
        // 2 * M_PI - полный оборот в радианах (360 градусов)
        // i / pointCount - доля оборота для текущей точки (от 0 до 1)
        // 2 * M_PI * i / pointCount - угол в радианах для точки i
        // M_PI - константа числа Пи 
        float angle = 2.0f * static_cast<float>(M_PI) * i / static_cast<float>(pointCount);
        sf::Vector2f point = {
            radius * std::cos(angle),  // X координата точки
            radius * std::sin(angle)   // Y координата точки
        };
        circle.setPoint(i, point);
    }
    circle.setFillColor(sf::Color::Blue);
    // 400, 300 - центр окна (800/2, 600/2)
    circle.setPosition({400.0f, 300.0f});
    float time = 0.0f;
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        time += 0.01f;
        
        // Вычисляем новую позицию круга по окружности
        // Используем тригонометрические функции для движения по кругу
        // 200.0f - радиус движения (расстояние от центра окна)
        // time - угол, который увеличивается со временем
        // std::cos(time) и std::sin(time) - координаты точки на окружности
        // 400.0f, 300.0f - центр окна (точка, вокруг которой движется круг)
        float x = 400.0f + 200.0f * std::cos(time);
        float y = 300.0f + 200.0f * std::sin(time);
        circle.setPosition({x, y});
        window.clear(sf::Color::White);
        window.draw(circle);
        window.display();
    }
    return 0;
}
