# Быстрый старт

## Сборка и запуск

### 1. Перейдите в каталог проекта
```bash
cd src/Lab2/sfml.1
```

### 2. Конфигурирование и сборка
```bash
cmake -G "MinGW Makefiles" -DSFML_DIR=C:/SFML302/lib/cmake/SFML .
cmake --build .
```

**Важно:** Если SFML установлен в другом месте, замените путь `C:/SFML302/lib/cmake/SFML` на правильный путь к вашему SFML.

### 3. Запуск программ

**Светофор (sfml1.1):**
```bash
01\01.exe
```

**Инициалы GVD (sfml1.2):**
```bash
02\02.exe
```

**Домик (sfml1.3):**
```bash
03\03.exe
```

## Git команды

### Первая настройка (если нужно)
```bash
git config --global user.email "ваш.email@example.com"
git config --global user.name "Ваше Имя"
```

### Добавление и коммит
```bash
git add .
git commit -m "Added SFML lab assignments"
```

### Отправка в репозиторий
```bash
git remote add origin https://github.com/V1DeeK/Project_Workshop_Basic_Tasks.git
git branch -M main
git push -u origin main
```

