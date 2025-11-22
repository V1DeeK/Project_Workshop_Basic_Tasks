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
// Зрачок двигается по эллипсу белка и не выходит за его границы
void updateEye(Eye& eye, sf::Vector2f mousePos)
{
    // Радиусы белка глаза (эллипса)
    // Эти значения должны совпадать с параметрами при создании белка
    const float whiteRadiusX = 80.0f;  // Радиус белка по оси X
    const float whiteRadiusY = 60.0f;  // Радиус белка по оси Y
    const float pupilRadius = 20.0f;   // Радиус зрачка (круглый)
    
    // Вычисляем вектор от центра глаза к позиции мыши
    float dx = mousePos.x - eye.center.x;
    float dy = mousePos.y - eye.center.y;
    
    // Если мышь находится точно в центре глаза, зрачок остается в центре
    if (dx == 0.0f && dy == 0.0f)
    {
        eye.pupil.setPosition(eye.center);
        return;
    }
    
    // Вычисляем максимальное смещение зрачка с учетом эллиптической формы белка
    // Зрачок должен оставаться внутри белка, поэтому учитываем его радиус
    const float maxOffsetX = whiteRadiusX - pupilRadius;
    const float maxOffsetY = whiteRadiusY - pupilRadius;
    
    // Нормализуем вектор направления (приводим к единичному вектору)
    float length = std::sqrt(dx * dx + dy * dy);
    float dirX = dx / length;
    float dirY = dy / length;
    
    // Находим точку пересечения направления с границей эллипса
    // Формула эллипса: (x/a)² + (y/b)² = 1
    // t = 1 / sqrt(dirX²/a² + dirY²/b²)
    float t = 1.0f / std::sqrt((dirX * dirX) / (maxOffsetX * maxOffsetX) + 
                               (dirY * dirY) / (maxOffsetY * maxOffsetY));
    
    // Вычисляем координаты точки на границе эллипса
    float ellipseX = t * dirX;
    float ellipseY = t * dirY;
    
    // Вычисляем расстояние от центра до мыши в нормализованных координатах эллипса
    float normalizedDx = dx / maxOffsetX;
    float normalizedDy = dy / maxOffsetY;
    float normalizedDistance = std::sqrt(normalizedDx * normalizedDx + normalizedDy * normalizedDy);
    
    // Проверяем, находится ли курсор мыши внутри белка глаза
    // Используем функцию isPointInEllipse для проверки
    bool mouseInEye = isPointInEllipse(mousePos, eye.center, whiteRadiusX, whiteRadiusY);
    
    // Если курсор находится внутри белка глаза
    if (mouseInEye)
    {
        // Зрачок следует за курсором мыши (находится под курсором)
        // Но проверяем, не выходит ли зрачок за границы белка
        if (normalizedDistance < 1.0f)
        {
            // Зрачок может следовать за мышью
            eye.pupil.setPosition(mousePos);
        }
        else
        {
            // Если зрачок выходит за границы, ограничиваем его границей эллипса
            float pupilX = eye.center.x + ellipseX;
            float pupilY = eye.center.y + ellipseY;
            eye.pupil.setPosition({pupilX, pupilY});
        }
    }
    else
    {
        // Если курсор вне белка, зрачок остается на границе эллипса в направлении мыши
        float pupilX = eye.center.x + ellipseX;
        float pupilY = eye.center.y + ellipseY;
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

