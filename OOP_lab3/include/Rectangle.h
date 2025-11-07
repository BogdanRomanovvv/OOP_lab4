#pragma once

#include "Figure.h"
#include <memory>
#include <cmath>
#include <stdexcept>

// прямоугольник который вписывается в окружность (диагонали равны)
template <Scalar T>
class Rectangle : public Figure<T>
{
private:
    std::unique_ptr<Point<T>> vertices[4]; // четыре угла прямоугольника

public:
    // конструктор по умолчанию
    Rectangle();

    // основной конструктор - принимает 4 точки
    Rectangle(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3, const Point<T> &p4);

    // копирующий конструктор
    Rectangle(const Rectangle<T> &other);

    // move конструктор
    Rectangle(Rectangle<T> &&other) noexcept;

    // оператор присваивания
    Rectangle<T> &operator=(const Rectangle<T> &other);

    // move присваивание
    Rectangle<T> &operator=(Rectangle<T> &&other) noexcept;

    // Деструктор
    ~Rectangle() override = default;

    // оператор сравнения двух прямоугольников
    bool operator==(const Rectangle<T> &other) const;

    // находим центр прямоугольника
    Point<T> getCenter() const override;

    // считаем площадь
    double getArea() const override;

    // выводим координаты в поток
    void print(std::ostream &os) const override;

    // читаем координаты из потока
    void read(std::istream &is) override;

    // клонируем объект
    std::unique_ptr<Figure<T>> clone() const override;

    // сравниваем с другой фигурой
    bool equals(const Figure<T> &other) const override;

    // возвращаем имя типа
    const char *getTypeName() const override;

    // получаем вершину по индексу
    Point<T> getVertex(size_t index) const;

private:
    // проверяем что прямоугольник правильный
    bool isValid() const;
};

// === РЕАЛИЗАЦИЯ ===

template <Scalar T>
Rectangle<T>::Rectangle()
{
    vertices[0] = std::make_unique<Point<T>>(T{}, T{});
    vertices[1] = std::make_unique<Point<T>>(T{}, T{});
    vertices[2] = std::make_unique<Point<T>>(T{}, T{});
    vertices[3] = std::make_unique<Point<T>>(T{}, T{});
}

template <Scalar T>
Rectangle<T>::Rectangle(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3, const Point<T> &p4)
{
    vertices[0] = std::make_unique<Point<T>>(p1);
    vertices[1] = std::make_unique<Point<T>>(p2);
    vertices[2] = std::make_unique<Point<T>>(p3);
    vertices[3] = std::make_unique<Point<T>>(p4);

    if (!isValid())
    {
        throw std::invalid_argument("Invalid rectangle: vertices must form a rectangle inscribed in a circle");
    }
}

template <Scalar T>
Rectangle<T>::Rectangle(const Rectangle<T> &other)
{
    for (size_t i = 0; i < 4; ++i)
    {
        vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]);
    }
}

template <Scalar T>
Rectangle<T>::Rectangle(Rectangle<T> &&other) noexcept
{
    for (size_t i = 0; i < 4; ++i)
    {
        vertices[i] = std::move(other.vertices[i]);
    }
}

template <Scalar T>
Rectangle<T> &Rectangle<T>::operator=(const Rectangle<T> &other)
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
Rectangle<T> &Rectangle<T>::operator=(Rectangle<T> &&other) noexcept
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
bool Rectangle<T>::operator==(const Rectangle<T> &other) const
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
Point<T> Rectangle<T>::getCenter() const
{
    T centerX = (vertices[0]->x + vertices[1]->x + vertices[2]->x + vertices[3]->x) / T(4);
    T centerY = (vertices[0]->y + vertices[1]->y + vertices[2]->y + vertices[3]->y) / T(4);
    return Point<T>(centerX, centerY);
}

template <Scalar T>
double Rectangle<T>::getArea() const
{
    // Площадь прямоугольника через длину двух соседних сторон
    double side1 = vertices[0]->distanceTo(*vertices[1]);
    double side2 = vertices[1]->distanceTo(*vertices[2]);
    return side1 * side2;
}

template <Scalar T>
void Rectangle<T>::print(std::ostream &os) const
{
    os << "Rectangle: ";
    for (size_t i = 0; i < 4; ++i)
    {
        os << *vertices[i];
        if (i < 3)
            os << ", ";
    }
}

template <Scalar T>
void Rectangle<T>::read(std::istream &is)
{
    for (size_t i = 0; i < 4; ++i)
    {
        T x, y;
        is >> x >> y;
        vertices[i] = std::make_unique<Point<T>>(x, y);
    }

    if (!isValid())
    {
        throw std::invalid_argument("Invalid rectangle: vertices must form a rectangle inscribed in a circle");
    }
}

template <Scalar T>
std::unique_ptr<Figure<T>> Rectangle<T>::clone() const
{
    return std::make_unique<Rectangle<T>>(*this);
}

template <Scalar T>
bool Rectangle<T>::equals(const Figure<T> &other) const
{
    const Rectangle<T> *otherRect = dynamic_cast<const Rectangle<T> *>(&other);
    if (otherRect == nullptr)
    {
        return false;
    }
    return *this == *otherRect;
}

template <Scalar T>
const char *Rectangle<T>::getTypeName() const
{
    return "Rectangle";
}

template <Scalar T>
Point<T> Rectangle<T>::getVertex(size_t index) const
{
    if (index >= 4)
    {
        throw std::out_of_range("Vertex index out of range");
    }
    return *vertices[index];
}

template <Scalar T>
bool Rectangle<T>::isValid() const
{
    // Проверяем, что все 4 точки заданы
    for (size_t i = 0; i < 4; ++i)
    {
        if (!vertices[i])
        {
            return false;
        }
    }

    // Для прямоугольника, вписанного в круг, диагонали должны быть равны
    // и пересекаться в центре окружности
    double diag1 = vertices[0]->distanceTo(*vertices[2]);
    double diag2 = vertices[1]->distanceTo(*vertices[3]);

    const double epsilon = 1e-6;
    if (std::abs(diag1 - diag2) > epsilon)
    {
        return false;
    }

    // Проверяем, что стороны перпендикулярны (через скалярное произведение)
    // Векторы соседних сторон
    T v1x = vertices[1]->x - vertices[0]->x;
    T v1y = vertices[1]->y - vertices[0]->y;
    T v2x = vertices[2]->x - vertices[1]->x;
    T v2y = vertices[2]->y - vertices[1]->y;

    // Скалярное произведение должно быть близко к нулю
    double dotProduct = static_cast<double>(v1x * v2x + v1y * v2y);
    if (std::abs(dotProduct) > epsilon)
    {
        return false;
    }

    return true;
}
