#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Game Loop");
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition({375, 275}); // Центр окна (800/2 - 50, 600/2 - 50)
    
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        sf::Vector2f pos = circle.getPosition();
        pos.x += 0.2f;
        // Если круг вышел за правую границу окна, возвращаем его в начало
        // 800 - ширина окна, 100 - диаметр круга (радиус 50 * 2)
        if (pos.x > 800 - 100)
        {
            pos.x = 0;
        }
        circle.setPosition(pos);
        window.clear(sf::Color::White);
        window.draw(circle);
        window.display();
    }
    return 0;
}

