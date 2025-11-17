# Минимальная версия CMake: 3.8
# cmake_minimum_required() - указывает минимальную версию CMake
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Имя проекта: sfml-lab-3
# project() - задает имя проекта
project(sfml-lab-3)

# Устанавливаем флаг для статической линковки SFML
# set() - устанавливает значение переменной
# SFML_STATIC_LIBRARIES - переменная для указания статической линковки
# TRUE - использовать статическую линковку (библиотеки встроены в исполняемый файл)
set(SFML_STATIC_LIBRARIES TRUE)

# Ищем необходимые зависимости для SFML
# find_package() - ищет установленный пакет
# REQUIRED - если пакет не найден, сборка прервется с ошибкой
# Freetype - библиотека для работы со шрифтами (требуется для SFML)
find_package(Freetype REQUIRED)
# JPEG - библиотека для работы с изображениями в формате JPEG (требуется для SFML)
find_package(JPEG REQUIRED)
# SFML 2 - ищем SFML версии 2
# COMPONENTS window graphics system - требуемые компоненты SFML
# window - работа с окнами
# graphics - работа с графикой
# system - системные функции
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

# Добавляем подкаталоги с заданиями
# add_subdirectory() - добавляет подкаталог в проект
add_subdirectory(00)
add_subdirectory(01)
add_subdirectory(sfml3.2)
add_subdirectory(sfml3.3)

