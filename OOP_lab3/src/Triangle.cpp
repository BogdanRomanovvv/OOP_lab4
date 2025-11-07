#include "Triangle.h"

// Конструктор по умолчанию
Triangle::Triangle() : vertices{Point(0, 0), Point(1, 0), Point(0, 1)} {}

// Конструктор с тремя вершинами
Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3)
    : vertices{p1, p2, p3}
{
    if (!isValid())
    {
        throw std::invalid_argument("Invalid triangle: points are collinear or identical");
    }
}

// Копирующий конструктор
Triangle::Triangle(const Triangle &other) : vertices(other.vertices) {}

// Перемещающий конструктор
Triangle::Triangle(Triangle &&other) noexcept : vertices(std::move(other.vertices)) {}

// Оператор копирующего присваивания
Triangle &Triangle::operator=(const Triangle &other)
{
    if (this != &other)
    {
        vertices = other.vertices;
    }
    return *this;
}

// Оператор перемещающего присваивания
Triangle &Triangle::operator=(Triangle &&other) noexcept
{
    if (this != &other)
    {
        vertices = std::move(other.vertices);
    }
    return *this;
}

// Оператор сравнения
bool Triangle::operator==(const Triangle &other) const
{
    return vertices[0] == other.vertices[0] &&
           vertices[1] == other.vertices[1] &&
           vertices[2] == other.vertices[2];
}

// Вычисление геометрического центра
Point Triangle::getCenter() const
{
    double centerX = (vertices[0].x + vertices[1].x + vertices[2].x) / 3.0;
    double centerY = (vertices[0].y + vertices[1].y + vertices[2].y) / 3.0;
    return Point(centerX, centerY);
}

// Вычисление площади по формуле Герона
double Triangle::getArea() const
{
    double a = vertices[0].distanceTo(vertices[1]);
    double b = vertices[1].distanceTo(vertices[2]);
    double c = vertices[2].distanceTo(vertices[0]);
    double s = (a + b + c) / 2.0;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

// Вывод координат вершин
void Triangle::print(std::ostream &os) const
{
    os << "Triangle: " << vertices[0] << " " << vertices[1] << " " << vertices[2];
}

// Чтение координат из потока
void Triangle::read(std::istream &is)
{
    is >> vertices[0] >> vertices[1] >> vertices[2];
    if (!isValid())
    {
        throw std::invalid_argument("Invalid triangle: points are collinear or identical");
    }
}

// Клонирование объекта
Figure *Triangle::clone() const
{
    return new Triangle(*this);
}

// Сравнение с другой фигурой
bool Triangle::equals(const Figure &other) const
{
    const Triangle *otherTriangle = dynamic_cast<const Triangle *>(&other);
    if (otherTriangle == nullptr)
    {
        return false;
    }
    return *this == *otherTriangle;
}

// Получение имени типа
const char *Triangle::getTypeName() const
{
    return "Triangle";
}

// Получение вершин
const std::array<Point, 3> &Triangle::getVertices() const
{
    return vertices;
}

// Валидация треугольника
bool Triangle::isValid() const
{
    // Проверка, что точки не совпадают
    if (vertices[0] == vertices[1] || vertices[1] == vertices[2] || vertices[2] == vertices[0])
    {
        return false;
    }

    // Проверка, что точки не лежат на одной прямой (площадь > 0)
    double area = std::abs(
        (vertices[1].x - vertices[0].x) * (vertices[2].y - vertices[0].y) -
        (vertices[2].x - vertices[0].x) * (vertices[1].y - vertices[0].y));

    return area > 1e-9;
}
