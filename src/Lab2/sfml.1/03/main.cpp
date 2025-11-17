#include <SFML/Graphics.hpp>


int main()
{
        sf::RenderWindow window(sf::VideoMode({600, 500}), "House");


    // ОСНОВАНИЕ ДОМА
    // Создаем прямоугольник для основного корпуса домика
    sf::RectangleShape houseBody(sf::Vector2f(320, 240));
    houseBody.setPosition({140, 220});
    houseBody.setFillColor(sf::Color(101, 67, 33)); 

    // Создаем треугольную крышу с помощью выпуклого многоугольника
    sf::ConvexShape roof;
    roof.setPointCount(3);
    roof.setPoint(0, sf::Vector2f(140, 220));  // Левый нижний угол
    roof.setPoint(1, sf::Vector2f(300, 120));  // Верхняя точка (центр крыши)
    roof.setPoint(2, sf::Vector2f(460, 220));  // Правый нижний угол
    roof.setFillColor(sf::Color(139, 69, 19));

    // Создаем прямоугольник для двери домика
    sf::RectangleShape door(sf::Vector2f(50, 100));
    door.setPosition({160, 360});
    door.setFillColor(sf::Color(50, 50, 50)); 

    // Создаем прямоугольник для трубы на крыше
    sf::RectangleShape chimney(sf::Vector2f(35, 70));
    chimney.setPosition({400, 150});
    chimney.setFillColor(sf::Color(50, 50, 50)); 
    
    // Первый круг дыма 
    sf::CircleShape smoke1(12);
    smoke1.setPosition({408, 130});
    smoke1.setFillColor(sf::Color(220, 220, 220));

    sf::CircleShape smoke2(18);
    smoke2.setPosition({415, 105});
    smoke2.setFillColor(sf::Color(200, 200, 200));
    
    // Третий круг дыма 
    sf::CircleShape smoke3(22);
    smoke3.setPosition({422, 75});
    smoke3.setFillColor(sf::Color(180, 180, 180));
    
    // Четвертый круг дыма 

    sf::CircleShape smoke4(18);
    smoke4.setPosition({430, 50});
    smoke4.setFillColor(sf::Color(160, 160, 160));
    
    sf::CircleShape smoke5(15);
    smoke5.setPosition({438, 30});
    smoke5.setFillColor(sf::Color(140, 140, 140));

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        window.clear(sf::Color::White);

        // Рисуем элементы домика в правильном порядке (сначала задние, потом передние)
        window.draw(houseBody);
        window.draw(roof);
        window.draw(door);
        window.draw(chimney);
        window.draw(smoke1); 
        window.draw(smoke2); 
        window.draw(smoke3); 
        window.draw(smoke4); 
        window.draw(smoke5); 
        window.display();
    }

    return 0;
}
