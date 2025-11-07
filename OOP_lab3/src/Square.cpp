#include "Square.h"

// Конструктор по умолчанию
Square::Square() : vertices{Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)} {}

// Конструктор с четырьмя вершинами
Square::Square(const Point &p1, const Point &p2, const Point &p3, const Point &p4)
    : vertices{p1, p2, p3, p4}
{
    if (!isValid())
    {
        throw std::invalid_argument("Invalid square: vertices do not form a square");
    }
}

// Копирующий конструктор
Square::Square(const Square &other) : vertices(other.vertices) {}

// Перемещающий конструктор
Square::Square(Square &&other) noexcept : vertices(std::move(other.vertices)) {}

// Оператор копирующего присваивания
Square &Square::operator=(const Square &other)
{
    if (this != &other)
    {
        vertices = other.vertices;
    }
    return *this;
}

// Оператор перемещающего присваивания
Square &Square::operator=(Square &&other) noexcept
{
    if (this != &other)
    {
        vertices = std::move(other.vertices);
    }
    return *this;
}

// Оператор сравнения
bool Square::operator==(const Square &other) const
{
    return vertices[0] == other.vertices[0] &&
           vertices[1] == other.vertices[1] &&
           vertices[2] == other.vertices[2] &&
           vertices[3] == other.vertices[3];
}

// Вычисление геометрического центра
Point Square::getCenter() const
{
    double centerX = (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) / 4.0;
    double centerY = (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) / 4.0;
    return Point(centerX, centerY);
}

// Вычисление площади
double Square::getArea() const
{
    // Используем формулу Шнурка (Shoelace formula)
    double area = 0.0;
    for (size_t i = 0; i < 4; ++i)
    {
        size_t j = (i + 1) % 4;
        area += vertices[i].x * vertices[j].y;
        area -= vertices[j].x * vertices[i].y;
    }
    return std::abs(area) / 2.0;
}

// Вывод координат вершин
void Square::print(std::ostream &os) const
{
    os << "Square: " << vertices[0] << " " << vertices[1] << " "
       << vertices[2] << " " << vertices[3];
}

// Чтение координат из потока
void Square::read(std::istream &is)
{
    is >> vertices[0] >> vertices[1] >> vertices[2] >> vertices[3];
    if (!isValid())
    {
        throw std::invalid_argument("Invalid square: vertices do not form a square");
    }
}

// Клонирование объекта
Figure *Square::clone() const
{
    return new Square(*this);
}

// Сравнение с другой фигурой
bool Square::equals(const Figure &other) const
{
    const Square *otherSquare = dynamic_cast<const Square *>(&other);
    if (otherSquare == nullptr)
    {
        return false;
    }
    return *this == *otherSquare;
}

// Получение имени типа
const char *Square::getTypeName() const
{
    return "Square";
}

// Получение вершин
const std::array<Point, 4> &Square::getVertices() const
{
    return vertices;
}

// Валидация квадрата
bool Square::isValid() const
{
    // Проверка, что все стороны равны
    double side1 = vertices[0].distanceTo(vertices[1]);
    double side2 = vertices[1].distanceTo(vertices[2]);
    double side3 = vertices[2].distanceTo(vertices[3]);
    double side4 = vertices[3].distanceTo(vertices[0]);

    // Проверка диагоналей
    double diag1 = vertices[0].distanceTo(vertices[2]);
    double diag2 = vertices[1].distanceTo(vertices[3]);

    const double eps = 1e-9;

    // Все стороны должны быть равны
    if (std::abs(side1 - side2) > eps ||
        std::abs(side2 - side3) > eps ||
        std::abs(side3 - side4) > eps)
    {
        return false;
    }

    // Диагонали должны быть равны
    if (std::abs(diag1 - diag2) > eps)
    {
        return false;
    }

    // Диагонали должны быть больше стороны (проверка на вырожденность)
    if (side1 < eps || diag1 < eps)
    {
        return false;
    }

    // Проверка прямых углов через скалярное произведение
    double dx1 = vertices[1].x - vertices[0].x;
    double dy1 = vertices[1].y - vertices[0].y;
    double dx2 = vertices[3].x - vertices[0].x;
    double dy2 = vertices[3].y - vertices[0].y;

    double dotProduct = dx1 * dx2 + dy1 * dy2;

    return std::abs(dotProduct) < eps;
}
