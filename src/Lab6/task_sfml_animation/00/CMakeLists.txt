# Добавляем исполняемый файл 00
add_executable(00 main.cpp)

# Пытаемся найти SFML 3, если не найдено - ищем SFML 2
find_package(SFML 3 COMPONENTS Graphics Window System QUIET)
if(NOT SFML_FOUND)
    find_package(SFML 2 COMPONENTS window graphics system)
    if(SFML_FOUND)
        target_compile_features(00 PUBLIC cxx_std_17)
        target_compile_definitions(00 PRIVATE SFML_STATIC)
        target_link_libraries(00 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    endif()
else()
    target_compile_features(00 PUBLIC cxx_std_17)
    target_include_directories(00 PRIVATE ${SFML_INCLUDE_DIR} C:/SFML302/include)
    target_link_libraries(00 PRIVATE SFML::Graphics SFML::Window SFML::System)
endif()

if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found! Please install SFML or set SFML_DIR to the path containing SFMLConfig.cmake")
endif()

