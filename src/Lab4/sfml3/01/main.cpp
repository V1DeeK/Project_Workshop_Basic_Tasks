
#include <SFML/Graphics.hpp>
#include <cmath>

// Структура Arrow - описывает стрелку, состоящую из треугольника и прямоугольника
// struct - ключевое слово для создания пользовательского типа данных
// Структура объединяет несколько переменных в один объект
struct Arrow
{
    // head - треугольник (наконечник стрелки)
    sf::ConvexShape head;
    
    // stem - прямоугольник (стержень стрелки)
    sf::RectangleShape stem;
    sf::Vector2f position;
    float rotation = 0;
};


// Arrow& arrow - ссылка на структуру Arrow
void initArrow(Arrow& arrow)
{
    arrow.head.setPointCount(3);
    arrow.head.setPoint(0, sf::Vector2f(0, -20));   // Верхняя вершина
    arrow.head.setPoint(1, sf::Vector2f(0, 20));    // Нижняя вершина
    arrow.head.setPoint(2, sf::Vector2f(40, 0));    // острие
    arrow.head.setFillColor(sf::Color::Red);

    arrow.stem.setSize(sf::Vector2f(100, 10));
    arrow.stem.setFillColor(sf::Color::Blue);

    // origin - точка, относительно которой происходит поворот и позиционирование
    arrow.stem.setOrigin({50, 5});
    // 400, 300 - центр окна размером 800x600
    arrow.position = {400, 300};
    arrow.rotation = 0;
}
void updateArrowElements(Arrow& arrow)
{
    arrow.stem.setPosition(arrow.position);
    // В SFML 3 setRotation принимает sf::Angle, используем sf::degrees() для конвертации из градусов
    arrow.stem.setRotation(sf::degrees(arrow.rotation * 180.0f / static_cast<float>(M_PI)));
    const float stemLength = 50.0f;  // Половина длины стержня
    sf::Vector2f headPosition = {
        arrow.position.x + stemLength * std::cos(arrow.rotation),  // X координата
        arrow.position.y + stemLength * std::sin(arrow.rotation)   // Y координата
    };
    arrow.head.setPosition(headPosition);
    // В SFML 3 setRotation принимает sf::Angle, используем sf::degrees() для конвертации из градусов
    arrow.head.setRotation(sf::degrees(arrow.rotation * 180.0f / static_cast<float>(M_PI)));
}
int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Arrow Following Mouse");
    Arrow arrow;
    initArrow(arrow);
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            
            if (event->is<sf::Event::Closed>())
            {
               
                window.close();
            }
            
            // движение мыши
            if (event->is<sf::Event::MouseMoved>())
            {
                // Получаем координаты курсора мыши
                // event->getIf<sf::Event::MouseMoved>() - получаем событие движения мыши
                // ->position() - получаем позицию мыши из события
                auto mouseEvent = event->getIf<sf::Event::MouseMoved>();
                if (mouseEvent)
                {
                    // Получаем позицию мыши в окне
                    // mouseEvent->position - координаты мыши (sf::Vector2i)
                    sf::Vector2i mousePos = mouseEvent->position;
                    
                    // Вычисляем вектор от центра стрелки к позиции мыши
                    // Это вектор направления, в котором должна смотреть стрелка
                    float dx = static_cast<float>(mousePos.x) - arrow.position.x;  // Разница по X
                    float dy = static_cast<float>(mousePos.y) - arrow.position.y;  // Разница по Y
                    
                    // Вычисляем угол поворота стрелки с помощью функции atan2
                    // std::atan2(y, x) - арктангенс, возвращает угол в радианах
                    // atan2 корректно обрабатывает все квадранты (углы от -π до π)
                    // dy, dx - порядок аргументов важен! (y, x), а не (x, y)
                    arrow.rotation = std::atan2(dy, dx);
                    
                    // Обновляем элементы стрелки с новым углом поворота
                    updateArrowElements(arrow);
                }
            }
        }
        window.clear(sf::Color::White);
        window.draw(arrow.stem);
        window.draw(arrow.head);
        window.display();
    }
    return 0;
}

