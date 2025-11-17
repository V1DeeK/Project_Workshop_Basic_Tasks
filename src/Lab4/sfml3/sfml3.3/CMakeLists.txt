# Добавляем исполняемый файл sfml3.3
add_executable(sfml3.3 main.cpp)

# Пытаемся найти SFML 3, если не найдено - ищем SFML 2
find_package(SFML 3 COMPONENTS Graphics Window System QUIET)
if(NOT SFML_FOUND)
    find_package(SFML 2 COMPONENTS window graphics system)
    if(SFML_FOUND)
        target_compile_features(sfml3.3 PUBLIC cxx_std_17)
        target_compile_definitions(sfml3.3 PRIVATE SFML_STATIC)
        target_link_libraries(sfml3.3 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    endif()
else()
    target_compile_features(sfml3.3 PUBLIC cxx_std_17)
    target_include_directories(sfml3.3 PRIVATE ${SFML_INCLUDE_DIR} C:/SFML302/include)
    target_link_libraries(sfml3.3 PRIVATE SFML::Graphics SFML::Window SFML::System)
endif()

if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found! Please install SFML or set SFML_DIR to the path containing SFMLConfig.cmake")
endif()

