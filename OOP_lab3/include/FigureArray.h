#pragma once

#include "Figure.h"
#include <stdexcept>

// массив для хранения указателей на фигуры (старая версия без шаблонов)
class FigureArray
{
private:
    Figure **data;   // тут хранятся указатели на фигуры
    size_t capacity; // сколько памяти выделено
    size_t size;     // сколько элементов реально есть

    // увеличиваем размер когда места не хватает
    void resize();

public:
    // конструктор по умолчанию
    FigureArray();

    // если сразу знаем размер
    explicit FigureArray(size_t initialCapacity);

    // копирующий конструктор
    FigureArray(const FigureArray &other);

    // move конструктор
    FigureArray(FigureArray &&other) noexcept;

    // оператор присваивания (копирование)
    FigureArray &operator=(const FigureArray &other);

    // оператор присваивания (перемещение)
    FigureArray &operator=(FigureArray &&other) noexcept;

    // деструктор
    ~FigureArray();

    // добавить фигуру в массив
    void add(Figure *figure);

    // удалить по индексу
    void remove(size_t index);

    // получить фигуру по индексу (const)
    const Figure *get(size_t index) const;

    // получить фигуру по индексу
    Figure *get(size_t index);

    // узнать сколько элементов
    size_t getSize() const;

    // посчитать общую площадь всех фигур
    double getTotalArea() const;

    // вывести все фигуры
    void printAll(std::ostream &os) const;

    // вывести центры и площади
    void printCentersAndAreas(std::ostream &os) const;

    // оператор индексации []  (константный)
    const Figure *operator[](size_t index) const;

    // оператор индексации []
    Figure *operator[](size_t index);
};
