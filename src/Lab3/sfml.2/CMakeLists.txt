# Минимальная версия CMake: 3.8
# cmake_minimum_required() - указывает минимальную версию CMake, необходимую для сборки проекта
# FATAL_ERROR - если версия CMake меньше указанной, сборка прервется с ошибкой
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Имя проекта: sfml-lab-2
# project() - задает имя проекта и настраивает переменные проекта
project(sfml-lab-2)

# Подкаталог 00 содержит ещё один CMakeLists.txt
# add_subdirectory() - добавляет подкаталог в проект, CMake найдет и выполнит CMakeLists.txt в этом подкаталоге
add_subdirectory(00)
add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)
add_subdirectory(sfml2.1)
add_subdirectory(sfml2.2)
