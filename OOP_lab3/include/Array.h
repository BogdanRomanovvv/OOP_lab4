#pragma once

#include <memory>
#include <stdexcept>
#include <utility>

// динамический массив на шаблонах
template <class T>
class Array
{
private:
    std::shared_ptr<T[]> data; // храним данные через shared_ptr
    size_t capacity;           // сколько всего можем хранить
    size_t size;               // сколько реально храним

    // функция для увеличения размера массива когда места не хватает
    void resize();

public:
    // конструктор по умолчанию
    Array();

    // конструктор если сразу знаем какой размер нужен
    explicit Array(size_t initialCapacity);

    // копирующий конструктор
    Array(const Array<T> &other);

    // move конструктор (для эффективности)
    Array(Array<T> &&other) noexcept;

    // оператор присваивания (копирование)
    Array<T> &operator=(const Array<T> &other);

    // оператор присваивания (перемещение)
    Array<T> &operator=(Array<T> &&other) noexcept;

    // деструктор
    ~Array() = default;

    // добавить элемент в конец
    void add(T element);

    // удалить элемент по индексу
    void remove(size_t index);

    // получить элемент (константная версия)
    const T &get(size_t index) const;

    // Получение элемента по индексу (неконстантная версия)
    T &get(size_t index);

    // Получение текущего размера массива
    size_t getSize() const;

    // Оператор индексации (константная версия)
    const T &operator[](size_t index) const;

    // Оператор индексации (неконстантная версия)
    T &operator[](size_t index);
};

// === РЕАЛИЗАЦИЯ МЕТОДОВ ===

template <class T>
Array<T>::Array() : data(nullptr), capacity(0), size(0)
{
}

template <class T>
Array<T>::Array(size_t initialCapacity) : capacity(initialCapacity), size(0)
{
    if (initialCapacity > 0)
    {
        data = std::shared_ptr<T[]>(new T[initialCapacity]);
    }
}

template <class T>
Array<T>::Array(const Array<T> &other) : capacity(other.capacity), size(other.size)
{
    if (other.capacity > 0)
    {
        data = std::shared_ptr<T[]>(new T[capacity]);
        // копируем все элементы
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }
}

template <class T>
Array<T>::Array(Array<T> &&other) noexcept
    : data(std::move(other.data)), capacity(other.capacity), size(other.size)
{
    // обнуляем исходный объект
    other.capacity = 0;
    other.size = 0;
}

template <class T>
Array<T> &Array<T>::operator=(const Array<T> &other)
{
    if (this != &other)
    {
        capacity = other.capacity;
        size = other.size;

        if (other.capacity > 0)
        {
            data = std::shared_ptr<T[]>(new T[capacity]);
            for (size_t i = 0; i < size; ++i)
            {
                data[i] = other.data[i];
            }
        }
        else
        {
            data = nullptr;
        }
    }
    return *this;
}

template <class T>
Array<T> &Array<T>::operator=(Array<T> &&other) noexcept
{
    if (this != &other)
    {
        data = std::move(other.data);
        capacity = other.capacity;
        size = other.size;

        other.capacity = 0;
        other.size = 0;
    }
    return *this;
}

template <class T>
void Array<T>::resize()
{
    size_t newCapacity = (capacity == 0) ? 2 : capacity * 2;
    std::shared_ptr<T[]> newData(new T[newCapacity]);

    // перемещаем элементы в новый массив используя move
    for (size_t i = 0; i < size; ++i)
    {
        newData[i] = std::move(data[i]);
    }

    data = std::move(newData);
    capacity = newCapacity;
}

template <class T>
void Array<T>::add(T element)
{
    if (size >= capacity) // если места нет расширяем массив
    {
        resize();
    }
    data[size++] = element;
}

template <class T>
void Array<T>::remove(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }

    // Перемещаем элементы влево с использованием move
    for (size_t i = index; i < size - 1; ++i)
    {
        data[i] = std::move(data[i + 1]);
    }
    --size;
}

template <class T>
const T &Array<T>::get(size_t index) const
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <class T>
T &Array<T>::get(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <class T>
size_t Array<T>::getSize() const
{
    return size;
}

template <class T>
const T &Array<T>::operator[](size_t index) const
{
    return get(index);
}

template <class T>
T &Array<T>::operator[](size_t index)
{
    return get(index);
}
