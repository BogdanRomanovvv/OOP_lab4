#pragma once

#include "Figure.h"
#include <memory>
#include <cmath>
#include <stdexcept>

// ромб - фигура вращения (все 4 стороны равны)
template <Scalar T>
class Rhombus : public Figure<T>
{
private:
    std::unique_ptr<Point<T>> vertices[4]; // четыре угла ромба

public:
    // конструктор по умолчанию
    Rhombus();

    // конструктор с точками
    Rhombus(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3, const Point<T> &p4);

    // копирующий конструктор
    Rhombus(const Rhombus<T> &other);

    // move конструктор
    Rhombus(Rhombus<T> &&other) noexcept;

    // оператор присваивания
    Rhombus<T> &operator=(const Rhombus<T> &other);

    // move присваивание
    Rhombus<T> &operator=(Rhombus<T> &&other) noexcept;

    // деструктор
    ~Rhombus() override = default;

    // оператор сравнения
    bool operator==(const Rhombus<T> &other) const;

    // находим центр ромба
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
    // Валидация ромба
    bool isValid() const;
};

// Реализация методов шаблонного класса

template <Scalar T>
Rhombus<T>::Rhombus()
{
    vertices[0] = std::make_unique<Point<T>>(T{}, T{});
    vertices[1] = std::make_unique<Point<T>>(T{}, T{});
    vertices[2] = std::make_unique<Point<T>>(T{}, T{});
    vertices[3] = std::make_unique<Point<T>>(T{}, T{});
}

template <Scalar T>
Rhombus<T>::Rhombus(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3, const Point<T> &p4)
{
    vertices[0] = std::make_unique<Point<T>>(p1);
    vertices[1] = std::make_unique<Point<T>>(p2);
    vertices[2] = std::make_unique<Point<T>>(p3);
    vertices[3] = std::make_unique<Point<T>>(p4);

    if (!isValid())
    {
        throw std::invalid_argument("Invalid rhombus: all sides must be equal");
    }
}

template <Scalar T>
Rhombus<T>::Rhombus(const Rhombus<T> &other)
{
    for (size_t i = 0; i < 4; ++i)
    {
        vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }
}

template <Scalar T>
Rhombus<T>::Rhombus(Rhombus<T> &&other) noexcept
{
    for (size_t i = 0; i < 4; ++i)
    {
        vertices[i] = std::move(other.vertices[i]);
    }
}

template <Scalar T>
Rhombus<T> &Rhombus<T>::operator=(const Rhombus<T> &other)
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
Rhombus<T> &Rhombus<T>::operator=(Rhombus<T> &&other) noexcept
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
bool Rhombus<T>::operator==(const Rhombus<T> &other) const
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
Point<T> Rhombus<T>::getCenter() const
{
    // Центр ромба - пересечение диагоналей
    T centerX = (vertices[0]->x + vertices[2]->x) / T(2);
    T centerY = (vertices[0]->y + vertices[2]->y) / T(2);
    return Point<T>(centerX, centerY);
}

template <Scalar T>
double Rhombus<T>::getArea() const
{
    // Площадь ромба через диагонали: S = (d1 * d2) / 2
    double d1 = vertices[0]->distanceTo(*vertices[2]);
    double d2 = vertices[1]->distanceTo(*vertices[3]);
    return (d1 * d2) / 2.0;
}

template <Scalar T>
void Rhombus<T>::print(std::ostream &os) const
{
    os << "Rhombus: ";
    for (size_t i = 0; i < 4; ++i)
    {
        os << *vertices[i];
        if (i < 3)
            os << ", ";
    }
}

template <Scalar T>
void Rhombus<T>::read(std::istream &is)
{
    for (size_t i = 0; i < 4; ++i)
    {
        T x, y;
        is >> x >> y;
        vertices[i] = std::make_unique<Point<T>>(x, y);
    }

    if (!isValid())
    {
        throw std::invalid_argument("Invalid rhombus: all sides must be equal");
    }
}

template <Scalar T>
std::unique_ptr<Figure<T>> Rhombus<T>::clone() const
{
    return std::make_unique<Rhombus<T>>(*this);
}

template <Scalar T>
bool Rhombus<T>::equals(const Figure<T> &other) const
{
    const Rhombus<T> *otherRhombus = dynamic_cast<const Rhombus<T> *>(&other);
    if (otherRhombus == nullptr)
    {
        return false;
    }
    return *this == *otherRhombus;
}

template <Scalar T>
const char *Rhombus<T>::getTypeName() const
{
    return "Rhombus";
}

template <Scalar T>
Point<T> Rhombus<T>::getVertex(size_t index) const
{
    if (index >= 4)
    {
        throw std::out_of_range("Vertex index out of range");
    }
    return *vertices[index];
}

template <Scalar T>
bool Rhombus<T>::isValid() const
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

    // Для ромба все стороны должны быть равны
    double side1 = vertices[0]->distanceTo(*vertices[1]);
    double side2 = vertices[1]->distanceTo(*vertices[2]);
    double side3 = vertices[2]->distanceTo(*vertices[3]);
    double side4 = vertices[3]->distanceTo(*vertices[0]);

    if (std::abs(side1 - side2) > epsilon ||
        std::abs(side2 - side3) > epsilon ||
        std::abs(side3 - side4) > epsilon)
    {
        return false;
    }

    // Проверяем, что диагонали пересекаются в центре
    T centerX1 = (vertices[0]->x + vertices[2]->x) / T(2);
    T centerY1 = (vertices[0]->y + vertices[2]->y) / T(2);
    T centerX2 = (vertices[1]->x + vertices[3]->x) / T(2);
    T centerY2 = (vertices[1]->y + vertices[3]->y) / T(2);

    if constexpr (std::is_floating_point_v<T>)
    {
        if (std::abs(centerX1 - centerX2) > epsilon || std::abs(centerY1 - centerY2) > epsilon)
        {
            return false;
        }
    }
    else
    {
        if (centerX1 != centerX2 || centerY1 != centerY2)
        {
            return false;
        }
    }

    return true;
}
