#pragma once

#include "Figure.h"
#include <array>
#include <cmath>
#include <stdexcept>

// Класс квадрата
class Square : public Figure
{
private:
    std::array<Point, 4> vertices;

public:
    // Конструктор по умолчанию
    Square();

    // Конструктор с четырьмя вершинами
    Square(const Point &p1, const Point &p2, const Point &p3, const Point &p4);

    // Копирующий конструктор
    Square(const Square &other);

    // Перемещающий конструктор
    Square(Square &&other) noexcept;

    // Оператор копирующего присваивания
    Square &operator=(const Square &other);

    // Оператор перемещающего присваивания
    Square &operator=(Square &&other) noexcept;

    // Деструктор
    ~Square() override = default;

    // Оператор сравнения
    bool operator==(const Square &other) const;

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
    const std::array<Point, 4> &getVertices() const;

private:
    // Валидация квадрата
    bool isValid() const;
};
