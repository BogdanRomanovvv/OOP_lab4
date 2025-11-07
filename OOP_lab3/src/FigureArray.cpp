#include "FigureArray.h"
#include <iomanip>

// Конструктор по умолчанию
FigureArray::FigureArray() : data(nullptr), capacity(0), size(0) {}

// Конструктор с начальной емкостью
FigureArray::FigureArray(size_t initialCapacity)
    : data(new Figure *[initialCapacity]),
      capacity(initialCapacity),
      size(0)
{
    for (size_t i = 0; i < capacity; ++i)
    {
        data[i] = nullptr;
    }
}

// Копирующий конструктор
FigureArray::FigureArray(const FigureArray &other)
    : data(new Figure *[other.capacity]),
      capacity(other.capacity),
      size(other.size)
{
    for (size_t i = 0; i < capacity; ++i)
    {
        data[i] = nullptr;
    }
    for (size_t i = 0; i < size; ++i)
    {
        data[i] = other.data[i]->clone();
    }
}

// Перемещающий конструктор
FigureArray::FigureArray(FigureArray &&other) noexcept
    : data(other.data), capacity(other.capacity), size(other.size)
{
    other.data = nullptr;
    other.capacity = 0;
    other.size = 0;
}

// Оператор копирующего присваивания
FigureArray &FigureArray::operator=(const FigureArray &other)
{
    if (this != &other)
    {
        // Освобождаем старые данные
        for (size_t i = 0; i < size; ++i)
        {
            delete data[i];
        }
        delete[] data;

        // Копируем новые данные
        capacity = other.capacity;
        size = other.size;
        data = new Figure *[capacity];

        for (size_t i = 0; i < capacity; ++i)
        {
            data[i] = nullptr;
        }
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = other.data[i]->clone();
        }
    }
    return *this;
}

// Оператор перемещающего присваивания
FigureArray &FigureArray::operator=(FigureArray &&other) noexcept
{
    if (this != &other)
    {
        // Освобождаем старые данные
        for (size_t i = 0; i < size; ++i)
        {
            delete data[i];
        }
        delete[] data;

        // Перемещаем данные
        data = other.data;
        capacity = other.capacity;
        size = other.size;

        // Обнуляем источник
        other.data = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    return *this;
}

// Деструктор
FigureArray::~FigureArray()
{
    for (size_t i = 0; i < size; ++i)
    {
        delete data[i];
    }
    delete[] data;
}

// Увеличение емкости массива
void FigureArray::resize()
{
    size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
    Figure **newData = new Figure *[newCapacity];

    for (size_t i = 0; i < newCapacity; ++i)
    {
        newData[i] = nullptr;
    }

    for (size_t i = 0; i < size; ++i)
    {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

// Добавление фигуры в массив
void FigureArray::add(Figure *figure)
{
    if (size >= capacity)
    {
        resize();
    }
    data[size++] = figure;
}

// Удаление фигуры по индексу
void FigureArray::remove(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }

    // Удаляем фигуру
    delete data[index];

    // Сдвигаем элементы влево
    for (size_t i = index; i < size - 1; ++i)
    {
        data[i] = data[i + 1];
    }

    data[size - 1] = nullptr;
    --size;
}

// Получение фигуры по индексу (константная версия)
const Figure *FigureArray::get(size_t index) const
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Получение фигуры по индексу (неконстантная версия)
Figure *FigureArray::get(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

// Получение текущего размера массива
size_t FigureArray::getSize() const
{
    return size;
}

// Вычисление общей площади всех фигур
double FigureArray::getTotalArea() const
{
    double totalArea = 0.0;
    for (size_t i = 0; i < size; ++i)
    {
        totalArea += static_cast<double>(*data[i]);
    }
    return totalArea;
}

// Печать всех фигур
void FigureArray::printAll(std::ostream &os) const
{
    for (size_t i = 0; i < size; ++i)
    {
        os << i << ": " << *data[i] << std::endl;
    }
}

// Печать информации о центрах и площадях
void FigureArray::printCentersAndAreas(std::ostream &os) const
{
    os << std::fixed << std::setprecision(4);
    for (size_t i = 0; i < size; ++i)
    {
        Point center = data[i]->getCenter();
        double area = static_cast<double>(*data[i]);
        os << i << ": " << data[i]->getTypeName()
           << " - Center: " << center
           << ", Area: " << area << std::endl;
    }
}

// Оператор индексации (константная версия)
const Figure *FigureArray::operator[](size_t index) const
{
    return get(index);
}

// Оператор индексации (неконстантная версия)
Figure *FigureArray::operator[](size_t index)
{
    return get(index);
}
