// Подключаем библиотеку SFML для работы с графикой
#include <SFML/Graphics.hpp>
// Подключаем библиотеку для математических функций (atan2, sqrt)
#include <cmath>

// Структура Eye - описывает один глаз, состоящий из белка и зрачка
struct Eye
{
    // white - белок глаза (эллипс)
    sf::ConvexShape white;
    
    // pupil - зрачок глаза (эллипс)
    sf::ConvexShape pupil;
    
    // center - центр глаза в окне
    sf::Vector2f center;
    
    // maxRadius - максимальный радиус движения зрачка
    float maxRadius;
};

// Функция создания эллипса через ConvexShape
void createEllipse(sf::ConvexShape& shape, float radiusX, float radiusY, int pointCount)
{
    // Устанавливаем количество вершин многоугольника
    shape.setPointCount(pointCount);
    
    // Цикл для создания точек эллипса
    for (int i = 0; i < pointCount; ++i)
    {
        // Вычисляем угол для текущей точки
        float angle = 2.0f * static_cast<float>(M_PI) * i / static_cast<float>(pointCount);
        
        // Переводим полярные координаты в декартовы для эллипса
        sf::Vector2f point = {
            radiusX * std::cos(angle),
            radiusY * std::sin(angle)
        };
        
        // Устанавливаем координаты точки
        shape.setPoint(i, point);
    }
}

// Функция проверки, находится ли точка внутри эллипса
// bool - возвращает true или false (находится ли точка внутри)
// isPointInEllipse() - имя функции
// sf::Vector2f point - точка для проверки
// sf::Vector2f center - центр эллипса
// float radiusX, float radiusY - радиусы эллипса по осям X и Y
bool isPointInEllipse(sf::Vector2f point, sf::Vector2f center, float radiusX, float radiusY)
{
    // Вычисляем смещение точки относительно центра эллипса
    float dx = point.x - center.x;  // Разница по X
    float dy = point.y - center.y;  // Разница по Y
    
    // Проверяем, находится ли точка внутри эллипса
    // Формула эллипса: (x/a)^2 + (y/b)^2 <= 1
    // Если это условие выполняется, точка находится внутри эллипса
    // radiusX и radiusY - полуоси эллипса (a и b в формуле)
    float normalizedX = dx / radiusX;  // Нормализованная координата X
    float normalizedY = dy / radiusY;   // Нормализованная координата Y
    
    // Вычисляем значение формулы эллипса
    // Если результат <= 1, точка находится внутри
    float ellipseValue = normalizedX * normalizedX + normalizedY * normalizedY;
    
    // Возвращаем true, если точка внутри эллипса, иначе false
    return ellipseValue <= 1.0f;
}

// Функция обновления позиции зрачка глаза с обработкой наведения на глаз
void updateEye(Eye& eye, sf::Vector2f mousePos)
{
    // Проверяем, находится ли курсор мыши внутри белка глаза
    // isPointInEllipse() - функция проверки точки внутри эллипса
    // mousePos - позиция мыши
    // eye.center - центр глаза
    // 80, 60 - радиусы белка глаза (те же, что при создании)
    bool mouseInEye = isPointInEllipse(mousePos, eye.center, 80.0f, 60.0f);
    
    // Если курсор находится внутри белка глаза
    if (mouseInEye)
    {
        // Зрачок следует за курсором мыши (находится под курсором)
        // Устанавливаем позицию зрачка точно на позицию мыши
        eye.pupil.setPosition(mousePos);
    }
    else
    {
        // Если курсор вне белка, зрачок смотрит в сторону курсора
        // (как в предыдущем задании)
        
        // Вычисляем вектор от центра глаза к позиции мыши
        float dx = mousePos.x - eye.center.x;
        float dy = mousePos.y - eye.center.y;
        
        // Вычисляем расстояние от центра глаза до мыши
        float distance = std::sqrt(dx * dx + dy * dy);
        
        // Ограничиваем расстояние максимальным радиусом движения зрачка
        distance = std::min(distance, eye.maxRadius);
        
        // Вычисляем угол направления к мыши
        float angle = std::atan2(dy, dx);
        
        // Вычисляем новую позицию зрачка
        float pupilX = eye.center.x + distance * std::cos(angle);
        float pupilY = eye.center.y + distance * std::sin(angle);
        
        // Устанавливаем новую позицию зрачка
        eye.pupil.setPosition({pupilX, pupilY});
    }
}

// Главная функция программы
int main()
{
    // === СОЗДАНИЕ ОКНА ===
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Eyes Following Mouse (Improved)");
    
    // === СОЗДАНИЕ ДВУХ ГЛАЗ ===
    Eye eyes[2];
    
    // === ИНИЦИАЛИЗАЦИЯ ЛЕВОГО ГЛАЗА ===
    eyes[0].center = {250.0f, 300.0f};
    eyes[0].maxRadius = 50.0f;
    
    createEllipse(eyes[0].white, 80.0f, 60.0f, 100);
    eyes[0].white.setFillColor(sf::Color::White);
    eyes[0].white.setPosition(eyes[0].center);
    
    createEllipse(eyes[0].pupil, 20.0f, 20.0f, 50);
    eyes[0].pupil.setFillColor(sf::Color::Black);
    eyes[0].pupil.setPosition(eyes[0].center);
    
    // === ИНИЦИАЛИЗАЦИЯ ПРАВОГО ГЛАЗА ===
    eyes[1].center = {550.0f, 300.0f};
    eyes[1].maxRadius = 50.0f;
    
    createEllipse(eyes[1].white, 80.0f, 60.0f, 100);
    eyes[1].white.setFillColor(sf::Color::White);
    eyes[1].white.setPosition(eyes[1].center);
    
    createEllipse(eyes[1].pupil, 20.0f, 20.0f, 50);
    eyes[1].pupil.setFillColor(sf::Color::Black);
    eyes[1].pupil.setPosition(eyes[1].center);
    
    // === ОСНОВНОЙ ЦИКЛ ПРОГРАММЫ (GAME LOOP) ===
    while (window.isOpen())
    {
        // === ЭТАП 1: ОБРАБОТКА СОБЫТИЙ ===
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            
            // Обрабатываем движение мыши
            if (event->is<sf::Event::MouseMoved>())
            {
                auto mouseEvent = event->getIf<sf::Event::MouseMoved>();
                if (mouseEvent)
                {
                    sf::Vector2i mousePosInt = mouseEvent->position;
                    sf::Vector2f mousePos = {
                        static_cast<float>(mousePosInt.x),
                        static_cast<float>(mousePosInt.y)
                    };
                    
                    // Обновляем оба глаза независимо друг от друга
                    // Каждый глаз обрабатывает наведение курсора отдельно
                    updateEye(eyes[0], mousePos);
                    updateEye(eyes[1], mousePos);
                }
            }
        }
        
        // === ЭТАП 2: ОБНОВЛЕНИЕ СОСТОЯНИЯ ===
        // Обновление происходит в обработчике событий мыши
        
        // === ЭТАП 3: ОТРИСОВКА ===
        window.clear(sf::Color(245, 245, 220));
        
        // Рисуем оба глаза
        for (int i = 0; i < 2; ++i)
        {
            window.draw(eyes[i].white);
            window.draw(eyes[i].pupil);
        }
        
        window.display();
    }
    
    return 0;
}

