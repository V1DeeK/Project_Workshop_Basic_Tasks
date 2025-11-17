// Подключаем библиотеку SFML для работы с графикой
#include <SFML/Graphics.hpp>
// Подключаем библиотеку для работы со временем
#include <SFML/System.hpp>
// Подключаем библиотеку для работы с векторами
#include <vector>
// Подключаем библиотеку для математических функций
#include <cmath>

// Главная функция программы
int main()
{
    // === СОЗДАНИЕ ОКНА ===
    // Создаем окно для отображения графики
    // sf::RenderWindow - класс для создания и управления окном
    // sf::VideoMode({800, 600}) - размер окна: ширина 800, высота 600
    // "Rotating Blocks" - заголовок окна
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Rotating Blocks");
    
    // === СОЗДАНИЕ МАССИВА ПРЯМОУГОЛЬНИКОВ ===
    // std::vector - динамический массив
    // sf::RectangleShape - класс для рисования прямоугольников
    std::vector<sf::RectangleShape> blocks;
    
    // Количество блоков для создания
    const int blockCount = 8;
    
    // Цикл для создания блоков
    for (int i = 0; i < blockCount; ++i)
    {
        // Создаем новый прямоугольник
        sf::RectangleShape block(sf::Vector2f(40, 40));
        
        // Устанавливаем цвет блока
        // Используем разные цвета для разных блоков
        switch (i % 4)
        {
            case 0: block.setFillColor(sf::Color::Red); break;
            case 1: block.setFillColor(sf::Color::Green); break;
            case 2: block.setFillColor(sf::Color::Blue); break;
            case 3: block.setFillColor(sf::Color::Yellow); break;
        }
        
        // Устанавливаем точку origin для блока
        // origin - точка, относительно которой происходит поворот
        // 20, 20 - центр блока (ширина/2, высота/2)
        block.setOrigin({20, 20});
        
        // Вычисляем начальную позицию блока по окружности
        // Используем тригонометрию для размещения блоков по кругу
        // 2 * M_PI * i / blockCount - угол для блока i
        // 200 - радиус окружности
        float angle = 2.0f * static_cast<float>(M_PI) * i / static_cast<float>(blockCount);
        float radius = 200.0f;
        float x = 400.0f + radius * std::cos(angle);  // Центр окна + смещение по X
        float y = 300.0f + radius * std::sin(angle);  // Центр окна + смещение по Y
        
        // Устанавливаем начальную позицию блока
        block.setPosition({x, y});
        
        // Добавляем блок в массив
        blocks.push_back(block);
    }
    
    // === ПЕРЕМЕННЫЕ ДЛЯ АНИМАЦИИ ===
    // Время для анимации
    float time = 0.0f;
    
    // === ОСНОВНОЙ ЦИКЛ ПРОГРАММЫ (GAME LOOP) ===
    // Создаем часы для измерения времени между кадрами
    sf::Clock clock;
    
    // Цикл работает, пока окно открыто
    while (window.isOpen())
    {
        // === ИЗМЕРЕНИЕ ВРЕМЕНИ ===
        // Получаем время, прошедшее с последнего кадра
        float deltaTime = clock.restart().asSeconds();
        
        // === ЭТАП 1: ОБРАБОТКА СОБЫТИЙ ===
        // Цикл обработки всех событий из очереди
        while (auto event = window.pollEvent())
        {
            // Проверяем, является ли событие закрытием окна
            if (event->is<sf::Event::Closed>())
            {
                // Закрываем окно, если пользователь нажал на крестик
                window.close();
            }
        }
        
        // === ЭТАП 2: ОБНОВЛЕНИЕ СОСТОЯНИЯ (АНИМАЦИЯ) ===
        // Увеличиваем время для создания анимации
        time += deltaTime;
        
        // Обновляем позиции и повороты всех блоков
        for (size_t i = 0; i < blocks.size(); ++i)
        {
            // Вычисляем новый угол для блока
            // Блоки вращаются вокруг центра окна
            // 2 * M_PI * i / blockCount - начальный угол блока
            // time * 0.5f - скорость вращения (0.5 радиан в секунду)
            float angle = 2.0f * static_cast<float>(M_PI) * i / static_cast<float>(blockCount) + time * 0.5f;
            
            // Вычисляем новую позицию блока по окружности
            float radius = 200.0f;
            float x = 400.0f + radius * std::cos(angle);
            float y = 300.0f + radius * std::sin(angle);
            
            // Устанавливаем новую позицию блока
            blocks[i].setPosition({x, y});
            
            // Поворачиваем блок вокруг своей оси
            // time * 90.0f - скорость вращения блока (90 градусов в секунду)
            // i * 45.0f - начальный угол для каждого блока (создает разнообразие)
            float rotation = time * 90.0f + i * 45.0f;
            blocks[i].setRotation(rotation);
        }
        
        // === ЭТАП 3: ОТРИСОВКА ===
        // Очищаем окно белым цветом перед отрисовкой нового кадра
        window.clear(sf::Color::White);
        
        // Рисуем все блоки
        for (const auto& block : blocks)
        {
            window.draw(block);
        }
        
        // Отображаем все нарисованное на экране
        window.display();
    }
    
    // Возвращаем 0 - код успешного завершения программы
    return 0;
}

