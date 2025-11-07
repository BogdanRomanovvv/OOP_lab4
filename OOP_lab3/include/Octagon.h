#pragma once

#include "Figure.h"
#include <array>
#include <cmath>
#include <stdexcept>

// Класс правильного восьмиугольника (октагона)
class Octagon : public Figure
{
private:
    std::array<Point, 8> vertices;

public:
    // Конструктор по умолчанию
    Octagon();

    // Конструктор с восемью вершинами
    Octagon(const Point &p1, const Point &p2, const Point &p3, const Point &p4,
            const Point &p5, const Point &p6, const Point &p7, const Point &p8);

    // Копирующий конструктор
    Octagon(const Octagon &other);

    // Перемещающий конструктор
    Octagon(Octagon &&other) noexcept;

    // Оператор копирующего присваивания
    Octagon &operator=(const Octagon &other);

    // Оператор перемещающего присваивания
    Octagon &operator=(Octagon &&other) noexcept;

    // Деструктор
    ~Octagon() override = default;

    // Оператор сравнения
    bool operator==(const Octagon &other) const;

    // Вычисление геометрического центра
    Point getCenter() const override;

    // Вычисление площади
    double getArea() const override;

    // Вывод координат вершин
    void print(std::ostream &os) const override;

    // Чтение координат из потока
    // Чтение координат из потока
    void read(std::istream &is) override;

    // Клонирование объекта
    Figure *clone() const override;

    // Сравнение с другой фигурой
    bool equals(const Figure &other) const override;

    // Получение имени типа
    const char *getTypeName() const override;

    // Получение вершин
    const std::array<Point, 8> &getVertices() const;

private:
    // Валидация октагона
    bool isValid() const;
};
