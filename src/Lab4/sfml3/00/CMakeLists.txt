# Добавляем исполняемый файл 00
# add_executable() - создает исполняемый файл из указанных исходных файлов
add_executable(00 main.cpp)

# Включаем режим C++17 для цели сборки 00
# target_compile_features() - указывает возможности C++ для компиляции
# PUBLIC - эти возможности будут доступны и для других целей
# cxx_std_17 - стандарт C++17
target_compile_features(00 PUBLIC cxx_std_17)

