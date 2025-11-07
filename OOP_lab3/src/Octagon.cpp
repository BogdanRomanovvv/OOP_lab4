#include "Octagon.h"
#include <numbers>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Конструктор по умолчанию - создает правильный восьмиугольник с центром в (0,0) и радиусом 1
Octagon::Octagon()
{
    double radius = 1.0;
    for (size_t i = 0; i < 8; ++i)
    {
        double angle = 2.0 * M_PI * i / 8.0;
        vertices[i] = Point(radius * std::cos(angle), radius * std::sin(angle));
    }
}

// Конструктор с восемью вершинами
Octagon::Octagon(const Point &p1, const Point &p2, const Point &p3, const Point &p4,
                 const Point &p5, const Point &p6, const Point &p7, const Point &p8)
    : vertices{p1, p2, p3, p4, p5, p6, p7, p8}
{
    if (!isValid())
    {
        throw std::invalid_argument("Invalid octagon: vertices do not form a valid octagon");
    }
}

// Копирующий конструктор
Octagon::Octagon(const Octagon &other) : vertices(other.vertices) {}

// Перемещающий конструктор
Octagon::Octagon(Octagon &&other) noexcept : vertices(std::move(other.vertices)) {}

// Оператор копирующего присваивания
Octagon &Octagon::operator=(const Octagon &other)
{
    if (this != &other)
    {
        vertices = other.vertices;
    }
    return *this;
}

// Оператор перемещающего присваивания
Octagon &Octagon::operator=(Octagon &&other) noexcept
{
    if (this != &other)
    {
        vertices = std::move(other.vertices);
    }
    return *this;
}

// Оператор сравнения
bool Octagon::operator==(const Octagon &other) const
{
    for (size_t i = 0; i < 8; ++i)
    {
        if (!(vertices[i] == other.vertices[i]))
        {
            return false;
        }
    }
    return true;
}

// Вычисление геометрического центра
Point Octagon::getCenter() const
{
    double centerX = 0.0;
    double centerY = 0.0;
    for (const auto &vertex : vertices)
    {
        centerX += vertex.x;
        centerY += vertex.y;
    }
    return Point(centerX / 8.0, centerY / 8.0);
}

// Вычисление площади по формуле Шнурка (Shoelace formula)
double Octagon::getArea() const
{
    double area = 0.0;
    for (size_t i = 0; i < 8; ++i)
    {
        size_t j = (i + 1) % 8;
        area += vertices[i].x * vertices[j].y;
        area -= vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}

// Вывод координат вершин
void Octagon::print(std::ostream &os) const
{
    os << "Octagon: ";
    for (size_t i = 0; i < 8; ++i)
    {
        os << vertices[i];
        if (i < 7)
            os << " ";
    }
}

// Чтение координат из потока
void Octagon::read(std::istream &is)
{
    for (size_t i = 0; i < 8; ++i)
    {
        is >> vertices[i];
    }
    if (!isValid())
    {
        throw std::invalid_argument("Invalid octagon: vertices do not form a valid octagon");
    }
}

// Клонирование объекта
Figure *Octagon::clone() const
{
    return new Octagon(*this);
}

// Сравнение с другой фигурой
bool Octagon::equals(const Figure &other) const
{
    const Octagon *otherOctagon = dynamic_cast<const Octagon *>(&other);
    if (otherOctagon == nullptr)
    {
        return false;
    }
    return *this == *otherOctagon;
}

// Получение имени типа
const char *Octagon::getTypeName() const
{
    return "Octagon";
}

// Получение вершин
const std::array<Point, 8> &Octagon::getVertices() const
{
    return vertices;
}

// Валидация октагона
bool Octagon::isValid() const
{
    const double eps = 1e-9;

    // Проверка, что вершины не совпадают
    for (size_t i = 0; i < 8; ++i)
    {
        for (size_t j = i + 1; j < 8; ++j)
        {
            if (vertices[i] == vertices[j])
            {
                return false;
            }
        }
    }

    // Проверка, что площадь больше нуля
    double area = getArea();
    if (area < eps)
    {
        return false;
    }

    // Для правильного восьмиугольника все стороны должны быть примерно равны
    // Но мы допускаем любой выпуклый восьмиугольник
    // Проверим просто, что стороны существуют (имеют ненулевую длину)
    for (size_t i = 0; i < 8; ++i)
    {
        size_t j = (i + 1) % 8;
        double side = vertices[i].distanceTo(vertices[j]);
        if (side < eps)
        {
            return false;
        }
    }

    return true;
}
