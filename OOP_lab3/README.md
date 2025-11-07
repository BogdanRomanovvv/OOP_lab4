# Лабораторная работа №4 - Основы метапрограммирования

## Описание

Программа для работы с геометрическими фигурами с использованием шаблонов (templates) и умных указателей. Демонстрирует применение метапрограммирования в C++: шаблоны классов, концепты (concepts), умные указатели и семантику перемещения.

### Тема
Основы метапрограммирования в C++

### Цели
- Изучение механизмов работы с шаблонами в C++
- Применение концептов (concepts) для ограничения типов
- Использование умных указателей (`std::unique_ptr`, `std::shared_ptr`)
- Реализация пользовательского шаблонного контейнера `Array<T>`
- Изучение семантики перемещения (move semantics)

## Реализованные классы

### Шаблонные фигуры
- **Rectangle<T>** - Прямоугольник с типом координат T
- **Trapezoid<T>** - Трапеция с типом координат T
- **Rhombus<T>** - Ромб с типом координат T

### Вспомогательные классы
- **Point<T>** - Точка на плоскости с координатами типа T
- **Figure<T>** - Базовый абстрактный класс для всех фигур
- **Array<T>** - Пользовательский динамический массив (аналог `std::vector`)

### Концепт Scalar
```cpp
template <typename T>
concept Scalar = std::is_scalar_v<T>;
```
Ограничивает типы координат только скалярными типами (int, float, double и т.д.)


## Способы запуска

### 🐳 Способ 1: Docker 


#### Шаги

1. **Сборка Docker образа:**
```powershell
docker build -t oop_lab4 .
```

2. **Запуск контейнера:**
```powershell
docker run -it --rm -v ${PWD}:/workspace oop_lab4
```

3. **Внутри контейнера запустите программу:**
```bash
./build/lab4_main
```

4. **Запуск тестов:**
```bash
cd build
ctest --output-on-failure
```

#### Альтернативный запуск (без входа в контейнер)

**Запуск программы:**
```powershell
docker run -it --rm -v ${PWD}:/workspace oop_lab4 bash -c "./build/lab4_main"
```

**Запуск тестов:**
```powershell
docker run -it --rm -v ${PWD}:/workspace oop_lab4 bash -c "cd build && ctest --output-on-failure"
```

### 🔧 Способ 2: DevContainer в VS Code 


#### Шаги

1. **Откройте проект в VS Code**

2. **Откройте в DevContainer:**
   - Нажмите `F1`
   - Выберите `Remote-Containers: Reopen in Container`
   - Дождитесь сборки контейнера (первый раз занимает 2-5 минут)

3. **Проект автоматически сконфигурируется и соберется**

4. **Запуск программы:**
   - Откройте встроенный терминал (`Ctrl + ~`)
   - Выполните: `./build/lab4_main`

5. **Запуск тестов:**
```bash
cd build
ctest --output-on-failure
```

### 💻 Способ 3: Локальная сборка



#### Шаги

1. **Клонирование репозитория:**
```powershell
git clone <repository-url>
cd OOP_lab3
```

2. **Создание директории для сборки:**
```powershell
mkdir build
cd build
```

3. **Конфигурация проекта:**
```powershell
cmake -G Ninja ..
```

Или с использованием Make (если Ninja не установлен):
```powershell
cmake ..
```

4. **Сборка проекта:**
```powershell
cmake --build .
```

5. **Запуск программы:**
```powershell
.\lab4_main.exe
```

6. **Запуск тестов:**
```powershell
ctest --output-on-failure
```

Или напрямую:
```powershell
.\lab4_tests.exe
```