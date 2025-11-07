#pragma once

#include <iostream>
#include <cmath>
#include <concepts>

// проверяем что тип скалярный (int, double, float и тд)
template <typename T>
concept Scalar = std::is_scalar_v<T>;

// структура для точки на плоскости
template <Scalar T>
struct Point
{
    T x;
    T y;

    Point() : x(T{}), y(T{}) {}
    Point(T x, T y) : x(x), y(y) {}

    // конструктор копирования
    Point(const Point<T> &other) : x(other.x), y(other.y) {}

    // move конструктор
    Point(Point<T> &&other) noexcept : x(std::move(other.x)), y(std::move(other.y)) {}

    // оператор копирующего присваивания
    Point<T> &operator=(const Point<T> &other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    // move присваивание
    Point<T> &operator=(Point<T> &&other) noexcept
    {
        if (this != &other)
        {
            x = std::move(other.x);
            y = std::move(other.y);
        }
        return *this;
    }

    // сравнение двух точек (для double сравниваем с погрешностью)
    bool operator==(const Point<T> &other) const
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            return std::abs(x - other.x) < T(1e-9) && std::abs(y - other.y) < T(1e-9);
        }
        else
        {
            return x == other.x && y == other.y;
        }
    }

    bool operator!=(const Point<T> &other) const
    {
        return !(*this == other);
    }

    // расстояние до другой точки
    double distanceTo(const Point<T> &other) const
    {
        return std::sqrt(static_cast<double>((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y)));
    }
};

// вывод точки в поток
template <Scalar T>
inline std::ostream &operator<<(std::ostream &os, const Point<T> &pt)
{
    os << "(" << pt.x << ", " << pt.y << ")";
    return os;
}

// ввод точки из потока
template <Scalar T>
inline std::istream &operator>>(std::istream &is, Point<T> &pt)
{
    is >> pt.x >> pt.y;
    return is;
}
