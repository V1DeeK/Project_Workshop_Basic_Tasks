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
        sf::VideoMode({800, 600}), "Ellipse",
        sf::State::Windowed, settings);
    sf::ConvexShape ellipse;
    const int pointCount = 200;
    ellipse.setPointCount(pointCount);
    
    // Радиусы эллипса по осям X и Y
    // sf::Vector2f - вектор из двух float значений
    // 200.0f, 80.0f - радиус по горизонтали 200, по вертикали 80
    const sf::Vector2f ellipseRadius = {200.0f, 80.0f};
    for (int i = 0; i < pointCount; ++i)
    {
        // Вычисляем угол для текущей точки
        // 2 * M_PI - полный оборот в радианах (360 градусов)
        // i / pointCount - доля оборота для текущей точки (от 0 до 1)
        // 2 * M_PI * i / pointCount - угол в радианах для точки i
        float angle = 2.0f * static_cast<float>(M_PI) * i / static_cast<float>(pointCount);
        
        // Переводим полярные координаты в декартовы для эллипса
        // Для эллипса используем разные радиусы по осям X и Y
        // x = ellipseRadius.x * cos(angle) - горизонтальная координата
        // y = ellipseRadius.y * sin(angle) - вертикальная координата
        sf::Vector2f point = {
            ellipseRadius.x * std::cos(angle),  
            ellipseRadius.y * std::sin(angle)   
        };
        ellipse.setPoint(i, point);
    }
    ellipse.setFillColor(sf::Color::Green);
    ellipse.setPosition({400.0f, 300.0f});
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        window.draw(ellipse);
        window.display();
    }
    return 0;
}

