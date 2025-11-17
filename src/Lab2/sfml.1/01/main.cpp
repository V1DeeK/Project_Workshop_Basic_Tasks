// Подключаем библиотеку SFML для работы с графикой (Graphics.hpp содержит классы для рисования)
#include <SFML/Graphics.hpp>

// Главная функция программы - точка входа
int main()
{
    
    sf::RenderWindow window(sf::VideoMode({200, 500}), "Traffic Light");
    
    
    // Создаем прямоугольник для корпуса светофора
    sf::RectangleShape body(sf::Vector2f(180, 480));
    body.setPosition({10, 10});
    body.setFillColor(sf::Color(60, 60, 60));

    // Создаем круг для красного сигнала светофора
    sf::CircleShape redLight(60);
    redLight.setPosition({40, 30}); // Центр корпуса по X: 10 + 180/2 = 100 Позиция круга: центр - радиус = 100 - 60 = 40 По Y: отступ 30 пикселей от верха (10 + 20)
    redLight.setFillColor(sf::Color::Red);
    sf::CircleShape yellowLight(60);
    
    yellowLight.setPosition({40, 170});// Устанавливаем позицию желтого круга: X=40 (центрирован), Y=170 (средняя позиция)
    yellowLight.setFillColor(sf::Color::Yellow);
    
    sf::CircleShape greenLight(60);
   
    greenLight.setPosition({40, 310}); // Устанавливаем позицию зеленого круга: X=40 (центрирован), Y=310 (нижняя позиция)
    greenLight.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
           
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
        window.clear(sf::Color::White);
        window.draw(body);
        window.draw(redLight);
        window.draw(yellowLight);
        window.draw(greenLight);
        window.display();
    }
    return 0;
}
