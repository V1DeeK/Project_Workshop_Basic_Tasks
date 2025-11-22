cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(sfml-lab-3)

# Пытаемся найти SFML 3, если не найдено - ищем SFML 2
find_package(SFML 3 COMPONENTS Graphics Window System QUIET)
if(NOT SFML_FOUND)
    find_package(SFML 2 COMPONENTS window graphics system)
    if(SFML_FOUND)
        # SFML 2 specific settings
    endif()
else()
    # SFML 3 specific settings
endif()

if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found! Please install SFML or set SFML_DIR to the path containing SFMLConfig.cmake")
endif()

add_subdirectory(00)
add_subdirectory(01)
add_subdirectory(sfml3.2)
add_subdirectory(sfml3.3)

