# Лабораторная работа по SFML

Эта лабораторная работа содержит задания по работе с библиотекой SFML (Simple Fast Multimedia Library) для создания графических приложений на C++.

## Структура проекта

```
sfml.1/
├── CMakeLists.txt          # Основной файл конфигурации CMake
├── 00/                     # Простая программа A+B
│   ├── CMakeLists.txt
│   └── main.cpp
├── 01/                     # Задание sfml1.1 - Светофор
│   ├── CMakeLists.txt
│   └── main.cpp
├── 02/                     # Задание sfml1.2 - Инициалы GVD
│   ├── CMakeLists.txt
│   └── main.cpp
└── 03/                     # Задание sfml1.3 - Домик
    ├── CMakeLists.txt
    └── main.cpp
```

## Требования

- Компилятор C++ с поддержкой C++17 (MinGW, MSVC, GCC, Clang)
- CMake версии 3.8 или выше
- SFML 2.x библиотека
- Git (для контроля версий)

## Установка и сборка

### 1. Перейдите в каталог проекта

```bash
cd src/Lab2/sfml.1
```

### 2. Конфигурирование проекта с помощью CMake

Для Windows с MinGW (если SFML установлен в C:/SFML302):
```bash
cmake -G "MinGW Makefiles" -DSFML_DIR=C:/SFML302/lib/cmake/SFML .
```

Если SFML установлен в другом месте, укажите правильный путь:
```bash
cmake -G "MinGW Makefiles" -DSFML_DIR=/path/to/sfml/lib/cmake/SFML .
```

Для Linux/Mac:
```bash
cmake -DSFML_DIR=/path/to/sfml/lib/cmake/SFML .
```

**Примечание:** Проект поддерживает как SFML 2, так и SFML 3. CMake автоматически определит версию и использует соответствующий API.

### 3. Сборка проекта

```bash
cmake --build .
```

Или используйте команду напрямую:
```bash
make
```

### 4. Запуск программ

После успешной сборки вы можете запустить следующие программы:

- **00.exe** - Простая программа A+B (консольная)
  ```bash
  00/00.exe
  ```

- **01.exe** - Светофор (sfml1.1)
  ```bash
  01/01.exe
  ```

- **02.exe** - Инициалы GVD (sfml1.2)
  ```bash
  02/02.exe
  ```

- **03.exe** - Домик (sfml1.3)
  ```bash
  03/03.exe
  ```

## Описание заданий

### Задание sfml1.1 - Светофор

Нарисован светофор с тремя кругами (красный, желтый, зеленый) внутри темно-серого прямоугольного корпуса. Размер окна: 200x500 пикселей.

### Задание sfml1.2 - Инициалы GVD

Нарисованы три буквы "G", "V", "D" с помощью прямоугольников. Буквы читаемые и аккуратные. Размер окна: 800x400 пикселей.

### Задание sfml1.3 - Домик

Нарисован домик с использованием:
- `RectangleShape` для основания дома, двери и трубы
- `ConvexShape` для треугольной крыши
- `CircleShape` для дыма из трубы

Размер окна: 600x500 пикселей.

## Работа с Git

### Инициализация репозитория (если еще не инициализирован)

```bash
git init
```

### Добавление файлов

```bash
git add CMakeLists.txt
git add 00/CMakeLists.txt
git add 00/main.cpp
git add 01/CMakeLists.txt
git add 01/main.cpp
git add 02/CMakeLists.txt
git add 02/main.cpp
git add 03/CMakeLists.txt
git add 03/main.cpp
```

### Проверка статуса

```bash
git status
```

### Фиксация изменений

```bash
git commit -m "Added SFML lab assignments: traffic light, initials GVD, and house"
```

### Настройка Git (если требуется)

```bash
git config --global user.email "ваш.email@example.com"
git config --global user.name "Ваше Имя"
```

### Очистка временных файлов сборки

```bash
git clean -fd
```

## Устранение проблем

### Ошибка: "Could not find SFML"

Убедитесь, что SFML установлен и доступен для CMake. Возможно, потребуется указать путь к SFML:

```bash
cmake -DSFML_ROOT=/path/to/sfml -G "MinGW Makefiles" .
```

### Ошибка компиляции

Проверьте, что:
1. Установлен компилятор C++17
2. SFML библиотека установлена корректно
3. Все зависимости (Freetype, JPEG) доступны

### Окно не открывается

Убедитесь, что:
1. Программа скомпилирована без ошибок
2. Все DLL файлы SFML находятся в той же папке, что и исполняемый файл
3. Графические драйверы обновлены

## Автор

Лабораторная работа выполнена в рамках курса по C++ и SFML.

