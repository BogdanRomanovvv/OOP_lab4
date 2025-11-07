#pragma once

#include <iostream>
#include <memory>
#include "Point.h"

// базовый класс для всех геометрических фигур (абстрактный)
template <Scalar T>
class Figure
{
public:
    // деструктор виртуальный чтобы правильно удалялись производные классы
    virtual ~Figure() = default;

    // возвращает центр фигуры
    virtual Point<T> getCenter() const = 0;

    // вычисляет площадь
    virtual double getArea() const = 0;

    // выводит координаты в поток
    virtual void print(std::ostream &os) const = 0;

    // читает координаты из потока
    virtual void read(std::istream &is) = 0;

    // клонирует объект (возвращает умный указатель)
    virtual std::unique_ptr<Figure<T>> clone() const = 0;

    // проверяет равенство двух фигур
    virtual bool equals(const Figure<T> &other) const = 0;

    // приведение к double - возвращает площадь
    explicit operator double() const
    {
        return getArea();
    }

    // получить имя типа фигуры (для вывода)
    virtual const char *getTypeName() const = 0;
};

// оператор вывода в поток
template <Scalar T>
inline std::ostream &operator<<(std::ostream &os, const Figure<T> &fig)
{
    fig.print(os);
    return os;
}

// оператор ввода из потока
template <Scalar T>
inline std::istream &operator>>(std::istream &is, Figure<T> &fig)
{
    fig.read(is);
    return is;
}
