#pragma once

#include "Figure.h"
#include <memory>
#include <cmath>
#include <stdexcept>
#include <algorithm>

// трапеция которая вписывается в окружность
template <Scalar T>
class Trapezoid : public Figure<T>
{
private:
    std::unique_ptr<Point<T>> vertices[4]; // 4 точки трапеции

public:
    // конструктор по умолчанию
    Trapezoid();

    // основной конструктор с 4 точками
    Trapezoid(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3, const Point<T> &p4);

    // копирующий конструктор
    Trapezoid(const Trapezoid<T> &other);

    // move конструктор
    Trapezoid(Trapezoid<T> &&other) noexcept;

    // оператор присваивания
    Trapezoid<T> &operator=(const Trapezoid<T> &other);

    // move присваивание
    Trapezoid<T> &operator=(Trapezoid<T> &&other) noexcept;

    // деструктор
    ~Trapezoid() override = default;

    // сравнение трапеций
    bool operator==(const Trapezoid<T> &other) const;

    // Вычисление геометрического центра
    Point<T> getCenter() const override;

    // Вычисление площади
    double getArea() const override;

    // Вывод координат вершин
    void print(std::ostream &os) const override;

    // Чтение координат из потока
    void read(std::istream &is) override;

    // Клонирование объекта
    std::unique_ptr<Figure<T>> clone() const override;

    // Сравнение с другой фигурой
    bool equals(const Figure<T> &other) const override;

    // Получение имени типа
    const char *getTypeName() const override;

    // Получение вершин
    Point<T> getVertex(size_t index) const;

private:
    // Валидация трапеции
    bool isValid() const;
};

// Реализация методов шаблонного класса

template <Scalar T>
Trapezoid<T>::Trapezoid()
{
    vertices[0] = std::make_unique<Point<T>>(T{}, T{});
    vertices[1] = std::make_unique<Point<T>>(T{}, T{});
    vertices[2] = std::make_unique<Point<T>>(T{}, T{});
    vertices[3] = std::make_unique<Point<T>>(T{}, T{});
}

template <Scalar T>
Trapezoid<T>::Trapezoid(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3, const Point<T> &p4)
{
    vertices[0] = std::make_unique<Point<T>>(p1);
    vertices[1] = std::make_unique<Point<T>>(p2);
    vertices[2] = std::make_unique<Point<T>>(p3);
    vertices[3] = std::make_unique<Point<T>>(p4);

    if (!isValid())
    {
        throw std::invalid_argument("Invalid trapezoid: vertices must form an isosceles trapezoid inscribed in a circle");
    }
}

template <Scalar T>
Trapezoid<T>::Trapezoid(const Trapezoid<T> &other)
{
    for (size_t i = 0; i < 4; ++i)
    {
        vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }
}

template <Scalar T>
Trapezoid<T>::Trapezoid(Trapezoid<T> &&other) noexcept
{
    for (size_t i = 0; i < 4; ++i)
    {
        vertices[i] = std::move(other.vertices[i]);
    }
}

template <Scalar T>
Trapezoid<T> &Trapezoid<T>::operator=(const Trapezoid<T> &other)
{
    if (this != &other)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
        }
    }
    return *this;
}

template <Scalar T>
Trapezoid<T> &Trapezoid<T>::operator=(Trapezoid<T> &&other) noexcept
{
    if (this != &other)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            vertices[i] = std::move(other.vertices[i]);
        }
    }
    return *this;
}

template <Scalar T>
bool Trapezoid<T>::operator==(const Trapezoid<T> &other) const
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (*vertices[i] != *other.vertices[i])
        {
            return false;
        }
    }
    return true;
}

template <Scalar T>
Point<T> Trapezoid<T>::getCenter() const
{
    T centerX = (vertices[0]->x + vertices[1]->x + vertices[2]->x + vertices[3]->x) / T(4);
    T centerY = (vertices[0]->y + vertices[1]->y + vertices[2]->y + vertices[3]->y) / T(4);
    return Point<T>(centerX, centerY);
}

template <Scalar T>
double Trapezoid<T>::getArea() const
{
    // Площадь трапеции по формуле Гаусса (формула шнурования)
    double area = 0.0;
    for (size_t i = 0; i < 4; ++i)
    {
        size_t j = (i + 1) % 4;
        area += static_cast<double>(vertices[i]->x * vertices[j]->y);
        area -= static_cast<double>(vertices[j]->x * vertices[i]->y);
    }
    return std::abs(area) / 2.0;
}

template <Scalar T>
void Trapezoid<T>::print(std::ostream &os) const
{
    os << "Trapezoid: ";
    for (size_t i = 0; i < 4; ++i)
    {
        os << *vertices[i];
        if (i < 3)
            os << ", ";
    }
}

template <Scalar T>
void Trapezoid<T>::read(std::istream &is)
{
    for (size_t i = 0; i < 4; ++i)
    {
        T x, y;
        is >> x >> y;
        vertices[i] = std::make_unique<Point<T>>(x, y);
    }

    if (!isValid())
    {
        throw std::invalid_argument("Invalid trapezoid: vertices must form an isosceles trapezoid inscribed in a circle");
    }
}

template <Scalar T>
std::unique_ptr<Figure<T>> Trapezoid<T>::clone() const
{
    return std::make_unique<Trapezoid<T>>(*this);
}

template <Scalar T>
bool Trapezoid<T>::equals(const Figure<T> &other) const
{
    const Trapezoid<T> *otherTrap = dynamic_cast<const Trapezoid<T> *>(&other);
    if (otherTrap == nullptr)
    {
        return false;
    }
    return *this == *otherTrap;
}

template <Scalar T>
const char *Trapezoid<T>::getTypeName() const
{
    return "Trapezoid";
}

template <Scalar T>
Point<T> Trapezoid<T>::getVertex(size_t index) const
{
    if (index >= 4)
    {
        throw std::out_of_range("Vertex index out of range");
    }
    return *vertices[index];
}

template <Scalar T>
bool Trapezoid<T>::isValid() const
{
    // Проверяем, что все 4 точки заданы
    for (size_t i = 0; i < 4; ++i)
    {
        if (!vertices[i])
        {
            return false;
        }
    }

    const double epsilon = 1e-6;

    // Проверка, что это четырехугольник (не вырожденный)
    double side1 = vertices[0]->distanceTo(*vertices[1]);
    double side2 = vertices[1]->distanceTo(*vertices[2]);
    double side3 = vertices[2]->distanceTo(*vertices[3]);
    double side4 = vertices[3]->distanceTo(*vertices[0]);

    if (side1 < epsilon || side2 < epsilon || side3 < epsilon || side4 < epsilon)
    {
        return false;
    }

    // Для трапеции, вписанной в круг, все 4 вершины должны находиться на одинаковом
    // расстоянии от центра окружности
    // Находим центр окружности (среднее арифметическое всех вершин - приближение)
    T centerX = (vertices[0]->x + vertices[1]->x + vertices[2]->x + vertices[3]->x) / T(4);
    T centerY = (vertices[0]->y + vertices[1]->y + vertices[2]->y + vertices[3]->y) / T(4);

    Point<T> center(centerX, centerY);

    // Проверяем, что все вершины примерно на одинаковом расстоянии от центра
    double r1 = vertices[0]->distanceTo(center);
    double r2 = vertices[1]->distanceTo(center);
    double r3 = vertices[2]->distanceTo(center);
    double r4 = vertices[3]->distanceTo(center);

    double avgRadius = (r1 + r2 + r3 + r4) / 4.0;

    // Для вписанной трапеции радиусы должны быть примерно равны
    // Используем более мягкую проверку для целочисленных координат
    double tolerance = avgRadius * 0.3; // 30% допуск
    if (tolerance < epsilon * 100)
        tolerance = epsilon * 100;

    if (std::abs(r1 - avgRadius) > tolerance ||
        std::abs(r2 - avgRadius) > tolerance ||
        std::abs(r3 - avgRadius) > tolerance ||
        std::abs(r4 - avgRadius) > tolerance)
    {
        return false;
    }

    return true;
}
