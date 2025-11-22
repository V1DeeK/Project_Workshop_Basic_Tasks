// Подключаем библиотеку SFML для работы с графикой
#include <SFML/Graphics.hpp>
// Подключаем библиотеку для математических функций (atan2, sqrt)
#include <cmath>

// Структура Eye - описывает один глаз, состоящий из белка и зрачка
// struct - ключевое слово для создания пользовательского типа данных
struct Eye
{
    // white - белок глаза (эллипс)
    // sf::ConvexShape - класс для рисования выпуклых многоугольников
    // Используем ConvexShape для создания эллипса (белок глаза)
    sf::ConvexShape white;
    
    // pupil - зрачок глаза (эллипс)
    // sf::ConvexShape - для создания эллипса (зрачок)
    sf::ConvexShape pupil;
    
    // center - центр глаза в окне
    // sf::Vector2f - вектор из двух float значений (x, y)
    sf::Vector2f center;
    
    // maxRadius - максимальный радиус движения зрачка
    // float - число с плавающей точкой
    // Зрачок не может выйти за пределы белка
    float maxRadius;
};

// Функция создания эллипса через ConvexShape
// void - функция не возвращает значение
// createEllipse() - имя функции
// sf::ConvexShape& shape - ссылка на ConvexShape (изменения применятся к оригиналу)
// float radiusX, float radiusY - радиусы эллипса по осям X и Y
// int pointCount - количество точек для аппроксимации эллипса
void createEllipse(sf::ConvexShape& shape, float radiusX, float radiusY, int pointCount)
{
    // Устанавливаем количество вершин многоугольника
    // setPointCount() - задает количество точек для фигуры
    shape.setPointCount(pointCount);
    
    // Цикл для создания точек эллипса
    // Используем полярные координаты для равномерного распределения точек
    for (int i = 0; i < pointCount; ++i)
    {
        // Вычисляем угол для текущей точки
        // 2 * M_PI - полный оборот в радианах (360 градусов)
        // i / pointCount - доля оборота для текущей точки (от 0 до 1)
        // 2 * M_PI * i / pointCount - угол в радианах для точки i
        float angle = 2.0f * static_cast<float>(M_PI) * i / static_cast<float>(pointCount);
        
        // Переводим полярные координаты в декартовы для эллипса
        // Для эллипса используем разные радиусы по осям X и Y
        // x = radiusX * cos(angle) - горизонтальная координата
        // y = radiusY * sin(angle) - вертикальная координата
        sf::Vector2f point = {
            radiusX * std::cos(angle),  // X координата точки
            radiusY * std::sin(angle)   // Y координата точки
        };
        
        // Устанавливаем координаты точки с номером i
        // setPoint() - задает координаты вершины многоугольника
        shape.setPoint(i, point);
    }
}

// Функция обновления позиции зрачка глаза
// Обновляет позицию зрачка в зависимости от позиции курсора мыши
// Зрачок двигается по эллипсу белка и не выходит за его границы
// void - функция не возвращает значение
// updateEye() - имя функции
// Eye& eye - ссылка на структуру Eye
// sf::Vector2f mousePos - позиция курсора мыши в окне
void updateEye(Eye& eye, sf::Vector2f mousePos)
{
    // Радиусы белка глаза (эллипса)
    // Эти значения должны совпадать с параметрами при создании белка
    const float whiteRadiusX = 80.0f;  // Радиус белка по оси X
    const float whiteRadiusY = 60.0f;  // Радиус белка по оси Y
    const float pupilRadius = 20.0f;   // Радиус зрачка (круглый)
    
    // Вычисляем вектор от центра глаза к позиции мыши
    // Это вектор направления, в котором должен смотреть зрачок
    float dx = mousePos.x - eye.center.x;  // Разница по X
    float dy = mousePos.y - eye.center.y;  // Разница по Y
    
    // Если мышь находится точно в центре глаза, зрачок остается в центре
    if (dx == 0.0f && dy == 0.0f)
    {
        eye.pupil.setPosition(eye.center);
        return;
    }
    
    // Вычисляем максимальное смещение зрачка с учетом эллиптической формы белка
    // Зрачок должен оставаться внутри белка, поэтому учитываем его радиус
    // Максимальное смещение по оси X: whiteRadiusX - pupilRadius
    // Максимальное смещение по оси Y: whiteRadiusY - pupilRadius
    const float maxOffsetX = whiteRadiusX - pupilRadius;
    const float maxOffsetY = whiteRadiusY - pupilRadius;
    
    // Нормализуем вектор направления (приводим к единичному вектору)
    // Это нужно для правильного вычисления точки на эллипсе
    float length = std::sqrt(dx * dx + dy * dy);
    float dirX = dx / length;  // Единичный вектор по X
    float dirY = dy / length;  // Единичный вектор по Y
    
    // Находим точку пересечения направления с границей эллипса
    // Формула эллипса: (x/a)² + (y/b)² = 1
    // Луч: x = t * dirX, y = t * dirY (от центра)
    // Подставляем в формулу: (t * dirX / a)² + (t * dirY / b)² = 1
    // t² * (dirX²/a² + dirY²/b²) = 1
    // t = 1 / sqrt(dirX²/a² + dirY²/b²)
    float t = 1.0f / std::sqrt((dirX * dirX) / (maxOffsetX * maxOffsetX) + 
                               (dirY * dirY) / (maxOffsetY * maxOffsetY));
    
    // Вычисляем координаты точки на границе эллипса
    float ellipseX = t * dirX;
    float ellipseY = t * dirY;
    
    // Вычисляем расстояние от центра до мыши в нормализованных координатах эллипса
    // Нормализуем координаты мыши относительно размеров эллипса
    float normalizedDx = dx / maxOffsetX;
    float normalizedDy = dy / maxOffsetY;
    float normalizedDistance = std::sqrt(normalizedDx * normalizedDx + normalizedDy * normalizedDy);
    
    // Если мышь находится внутри эллипса (нормализованное расстояние < 1)
    if (normalizedDistance < 1.0f)
    {
        // Зрачок следует за мышью (находится под курсором)
        eye.pupil.setPosition(mousePos);
    }
    else
    {
        // Если мышь вне эллипса, зрачок остается на границе эллипса
        // Устанавливаем позицию зрачка на границе эллипса в направлении мыши
        float pupilX = eye.center.x + ellipseX;
        float pupilY = eye.center.y + ellipseY;
        eye.pupil.setPosition({pupilX, pupilY});
    }
}

// Главная функция программы
int main()
{
    // === СОЗДАНИЕ ОКНА ===
    // Создаем окно для отображения графики
    // sf::RenderWindow - класс для создания и управления окном
    // sf::VideoMode({800, 600}) - размер окна: ширина 800, высота 600
    // "Eyes Following Mouse" - заголовок окна
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Eyes Following Mouse");
    
    // === СОЗДАНИЕ ДВУХ ГЛАЗ ===
    // Объявляем массив из двух глаз
    // Eye eyes[2] - массив из двух элементов типа Eye
    Eye eyes[2];
    
    // === ИНИЦИАЛИЗАЦИЯ ЛЕВОГО ГЛАЗА ===
    // Устанавливаем центр левого глаза
    // 250, 300 - позиция левого глаза (левая часть окна, центр по вертикали)
    eyes[0].center = {250.0f, 300.0f};
    // Устанавливаем максимальный радиус движения зрачка
    // 50 - зрачок может двигаться на расстояние до 50 пикселей от центра
    eyes[0].maxRadius = 50.0f;
    
    // Создаем белок левого глаза (большой эллипс)
    // createEllipse() - функция для создания эллипса
    // 80, 60 - радиусы эллипса (ширина 160, высота 120)
    // 100 - количество точек для аппроксимации (высокое качество)
    createEllipse(eyes[0].white, 80.0f, 60.0f, 100);
    // Устанавливаем цвет заливки белка - белый
    eyes[0].white.setFillColor(sf::Color::White);
    // Устанавливаем позицию белка
    eyes[0].white.setPosition(eyes[0].center);
    
    // Создаем зрачок левого глаза (маленький эллипс)
    // 20, 20 - радиусы зрачка (круг диаметром 40)
    // 50 - количество точек для аппроксимации
    createEllipse(eyes[0].pupil, 20.0f, 20.0f, 50);
    // Устанавливаем цвет заливки зрачка - черный
    eyes[0].pupil.setFillColor(sf::Color::Black);
    // Устанавливаем начальную позицию зрачка (в центре глаза)
    eyes[0].pupil.setPosition(eyes[0].center);
    
    // === ИНИЦИАЛИЗАЦИЯ ПРАВОГО ГЛАЗА ===
    // Устанавливаем центр правого глаза
    // 550, 300 - позиция правого глаза (правая часть окна, центр по вертикали)
    eyes[1].center = {550.0f, 300.0f};
    // Устанавливаем максимальный радиус движения зрачка
    eyes[1].maxRadius = 50.0f;
    
    // Создаем белок правого глаза
    createEllipse(eyes[1].white, 80.0f, 60.0f, 100);
    eyes[1].white.setFillColor(sf::Color::White);
    eyes[1].white.setPosition(eyes[1].center);
    
    // Создаем зрачок правого глаза
    createEllipse(eyes[1].pupil, 20.0f, 20.0f, 50);
    eyes[1].pupil.setFillColor(sf::Color::Black);
    eyes[1].pupil.setPosition(eyes[1].center);
    
    // === ОСНОВНОЙ ЦИКЛ ПРОГРАММЫ (GAME LOOP) ===
    // Цикл работает, пока окно открыто
    while (window.isOpen())
    {
        // === ЭТАП 1: ОБРАБОТКА СОБЫТИЙ ===
        // Цикл обработки всех событий из очереди
        // window.pollEvent() - извлекает событие из очереди (SFML 3 API)
        while (auto event = window.pollEvent())
        {
            // Проверяем, является ли событие закрытием окна
            if (event->is<sf::Event::Closed>())
            {
                // Закрываем окно, если пользователь нажал на крестик
                window.close();
            }
            
            // Обрабатываем движение мыши
            // Проверяем, является ли событие движением мыши
            if (event->is<sf::Event::MouseMoved>())
            {
                // Получаем координаты курсора мыши
                auto mouseEvent = event->getIf<sf::Event::MouseMoved>();
                if (mouseEvent)
                {
                    // Получаем позицию мыши в окне
                    // mouseEvent->position - координаты мыши (sf::Vector2i)
                    sf::Vector2i mousePosInt = mouseEvent->position;
                    // Преобразуем в float для вычислений
                    sf::Vector2f mousePos = {
                        static_cast<float>(mousePosInt.x),
                        static_cast<float>(mousePosInt.y)
                    };
                    
                    // Обновляем оба глаза независимо друг от друга
                    // Каждый глаз следит за курсором независимо
                    // updateEye() - функция обновления позиции зрачка
                    updateEye(eyes[0], mousePos);  // Обновляем левый глаз
                    updateEye(eyes[1], mousePos);  // Обновляем правый глаз
                }
            }
        }
        
        // === ЭТАП 2: ОБНОВЛЕНИЕ СОСТОЯНИЯ ===
        // В этом примере обновление происходит в обработчике событий мыши
        // Здесь можно добавить другую логику обновления
        
        // === ЭТАП 3: ОТРИСОВКА ===
        // Очищаем окно бежевым цветом перед отрисовкой нового кадра
        // sf::Color(245, 245, 220) - бежевый цвет (RGB)
        window.clear(sf::Color(245, 245, 220));
        
        // Рисуем оба глаза
        // Сначала рисуем белки, потом зрачки (чтобы зрачки были поверх)
        for (int i = 0; i < 2; ++i)
        {
            // Рисуем белок глаза
            // window.draw() - добавляет фигуру в буфер отрисовки
            window.draw(eyes[i].white);
            // Рисуем зрачок глаза
            window.draw(eyes[i].pupil);
        }
        
        // Отображаем все нарисованное на экране
        // window.display() - выводит содержимое буфера на экран
        window.display();
    }
    
    // Возвращаем 0 - код успешного завершения программы
    return 0;
}

