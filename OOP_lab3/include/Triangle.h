#pragma once

#include "Figure.h"
#include <array>
#include <cmath>
#include <stdexcept>

// Класс треугольника
class Triangle : public Figure
{
private:
    std::array<Point, 3> vertices;

public:
    // Конструктор по умолчанию
    Triangle();

    // Конструктор с тремя вершинами
    Triangle(const Point &p1, const Point &p2, const Point &p3);

    // Копирующий конструктор
    Triangle(const Triangle &other);

    // Перемещающий конструктор
    Triangle(Triangle &&other) noexcept;

    // Оператор копирующего присваивания
    Triangle &operator=(const Triangle &other);

    // Оператор перемещающего присваивания
    Triangle &operator=(Triangle &&other) noexcept;

    // Деструктор
    ~Triangle() override = default;

    // Оператор сравнения
    bool operator==(const Triangle &other) const;

    // Вычисление геометрического центра
    Point getCenter() const override;

    // Вычисление площади
    double getArea() const override;

    // Вывод координат вершин
    void print(std::ostream &os) const override;

    // Чтение координат из потока
    void read(std::istream &is) override;

    // Клонирование объекта
    Figure *clone() const override;

    // Сравнение с другой фигурой
    bool equals(const Figure &other) const override;

    // Получение имени типа
    const char *getTypeName() const override;

    // Получение вершин
    const std::array<Point, 3> &getVertices() const;

private:
    // Валидация треугольника
    bool isValid() const;
};
