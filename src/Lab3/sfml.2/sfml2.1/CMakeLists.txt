# Добавляем исполняемый файл sfml2.1
# add_executable() - создает исполняемый файл из указанных исходных файлов
# Первый аргумент - имя исполняемого файла, второй - список исходных файлов
add_executable(sfml2.1 main.cpp)

# Пытаемся найти SFML 3, если не найдено - ищем SFML 2
# find_package() - ищет установленную библиотеку SFML
# COMPONENTS Graphics Window System - требуемые компоненты SFML (графика, окно, система)
# QUIET - не выводить сообщения об ошибках, если библиотека не найдена
find_package(SFML 3 COMPONENTS Graphics Window System QUIET)

# Если SFML 3 не найден, пытаемся найти SFML 2
if(NOT SFML_FOUND)
    # Ищем SFML 2 с теми же компонентами
    find_package(SFML 2 COMPONENTS window graphics system)
    if(SFML_FOUND)
        # Включаем режим C++17 для цели сборки sfml2.1
        # target_compile_features() - указывает, какие возможности C++ требуются для компиляции
        # PUBLIC - эти возможности будут доступны и для других целей, которые связываются с этой
        # cxx_std_17 - стандарт C++17
        target_compile_features(sfml2.1 PUBLIC cxx_std_17)
        # Устанавливаем определение препроцессора для статической линковки SFML 2
        # target_compile_definitions() - добавляет определения препроцессора
        # PRIVATE - определение доступно только для этой цели
        # SFML_STATIC - указывает, что используется статическая линковка SFML
        target_compile_definitions(sfml2.1 PRIVATE SFML_STATIC)
        # Связываем библиотеки SFML 2 с исполняемым файлом
        # target_link_libraries() - связывает библиотеки с целью
        # ${SFML_LIBRARIES} - переменная, содержащая пути к библиотекам SFML
        # ${SFML_DEPENDENCIES} - переменная, содержащая зависимости SFML (например, OpenGL)
        target_link_libraries(sfml2.1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    endif()
else()
    # Если SFML 3 найден, используем его настройки
    # Включаем режим C++17
    target_compile_features(sfml2.1 PUBLIC cxx_std_17)
    # Добавляем пути к заголовочным файлам SFML 3
    # target_include_directories() - добавляет пути к заголовочным файлам
    # PRIVATE - пути доступны только для этой цели
    # ${SFML_INCLUDE_DIR} - переменная с путем к заголовочным файлам SFML
    # C:/SFML302/include - явный путь к заголовочным файлам SFML 3 (если переменная не установлена)
    target_include_directories(sfml2.1 PRIVATE ${SFML_INCLUDE_DIR} C:/SFML302/include)
    # Связываем библиотеки SFML 3 с исполняемым файлом
    # SFML::Graphics, SFML::Window, SFML::System - цели CMake для компонентов SFML 3
    target_link_libraries(sfml2.1 PRIVATE SFML::Graphics SFML::Window SFML::System)
endif()

# Если SFML не найден ни в версии 2, ни в версии 3
if(NOT SFML_FOUND)
    # Выводим сообщение об ошибке и прерываем сборку
    # message() - выводит сообщение
    # FATAL_ERROR - прерывает выполнение CMake с ошибкой
    message(FATAL_ERROR "SFML not found! Please install SFML or set SFML_DIR to the path containing SFMLConfig.cmake")
endif()

