# Добавляем исполняемый файл 01
# add_executable() - создает исполняемый файл из указанных исходных файлов
add_executable(01 main.cpp)

# Пытаемся найти SFML 3, если не найдено - ищем SFML 2
# find_package() - ищет установленный пакет SFML
# COMPONENTS Graphics Window System - требуемые компоненты SFML
# QUIET - не выводить сообщения, если пакет не найден
find_package(SFML 3 COMPONENTS Graphics Window System QUIET)

# Проверяем, найден ли SFML 3
# if(NOT SFML_FOUND) - если SFML 3 не найден
if(NOT SFML_FOUND)
    # Пытаемся найти SFML 2
    # В SFML 2 названия компонентов в нижнем регистре
    find_package(SFML 2 COMPONENTS window graphics system)
    # Если SFML 2 найден
    if(SFML_FOUND)
        # Указываем стандарт C++17 для SFML 2
        target_compile_features(01 PUBLIC cxx_std_17)
        # Определяем макрос SFML_STATIC для статической линковки
        target_compile_definitions(01 PRIVATE SFML_STATIC)
        # Связываем библиотеки SFML 2
        target_link_libraries(01 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    endif()
else()
    # SFML 3 использует другой синтаксис
    # Указываем стандарт C++17
    target_compile_features(01 PUBLIC cxx_std_17)
    # Добавляем директории с заголовочными файлами SFML 3
    # PRIVATE - эти директории нужны только для компиляции этой цели
    target_include_directories(01 PRIVATE ${SFML_INCLUDE_DIR} C:/SFML302/include)
    # Связываем библиотеки SFML 3 (используем современный синтаксис с ::)
    target_link_libraries(01 PRIVATE SFML::Graphics SFML::Window SFML::System)
endif()

# Если SFML не найден ни в версии 2, ни в версии 3
if(NOT SFML_FOUND)
    # Выводим ошибку и прерываем сборку
    # message(FATAL_ERROR ...) - выводит сообщение и останавливает сборку
    message(FATAL_ERROR "SFML not found! Please install SFML or set SFML_DIR to the path containing SFMLConfig.cmake")
endif()

