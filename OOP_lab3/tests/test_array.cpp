#include <gtest/gtest.h>
#include "Array.h"
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Rhombus.h"

// Тесты для шаблонного класса Array

TEST(ArrayTest, DefaultConstructor)
{
    Array<int> array;
    EXPECT_EQ(array.getSize(), 0);
}

TEST(ArrayTest, AddElement)
{
    Array<int> array;
    array.add(42);
    EXPECT_EQ(array.getSize(), 1);
    EXPECT_EQ(array[0], 42);
}

TEST(ArrayTest, AddMultipleElements)
{
    Array<int> array;
    array.add(1);
    array.add(2);
    array.add(3);

    EXPECT_EQ(array.getSize(), 3);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 3);
}

TEST(ArrayTest, RemoveElement)
{
    Array<int> array;
    array.add(10);
    array.add(20);
    array.add(30);

    array.remove(1);

    EXPECT_EQ(array.getSize(), 2);
    EXPECT_EQ(array[0], 10);
    EXPECT_EQ(array[1], 30);
}

TEST(ArrayTest, RemoveInvalidIndex)
{
    Array<int> array;
    array.add(10);

    EXPECT_THROW(array.remove(5), std::out_of_range);
}

TEST(ArrayTest, GetElement)
{
    Array<int> array;
    array.add(100);
    array.add(200);

    EXPECT_EQ(array.get(0), 100);
    EXPECT_EQ(array.get(1), 200);
}

TEST(ArrayTest, GetInvalidIndex)
{
    Array<int> array;
    EXPECT_THROW(array.get(0), std::out_of_range);
}

TEST(ArrayTest, IndexOperator)
{
    Array<int> array;
    array.add(42);
    array.add(84);

    EXPECT_EQ(array[0], 42);
    EXPECT_EQ(array[1], 84);
}

TEST(ArrayTest, CopyConstructor)
{
    Array<int> array1;
    array1.add(1);
    array1.add(2);
    array1.add(3);

    Array<int> array2(array1);

    EXPECT_EQ(array1.getSize(), array2.getSize());
    EXPECT_EQ(array1[0], array2[0]);
    EXPECT_EQ(array1[1], array2[1]);
    EXPECT_EQ(array1[2], array2[2]);
}

TEST(ArrayTest, MoveConstructor)
{
    Array<int> array1;
    array1.add(10);
    array1.add(20);

    size_t size = array1.getSize();

    Array<int> array2(std::move(array1));

    EXPECT_EQ(array2.getSize(), size);
    EXPECT_EQ(array2[0], 10);
    EXPECT_EQ(array2[1], 20);
    EXPECT_EQ(array1.getSize(), 0);
}

TEST(ArrayTest, CopyAssignment)
{
    Array<int> array1;
    Array<int> array2;

    array1.add(100);
    array1.add(200);

    array2 = array1;

    EXPECT_EQ(array1.getSize(), array2.getSize());
    EXPECT_EQ(array1[0], array2[0]);
    EXPECT_EQ(array1[1], array2[1]);
}

TEST(ArrayTest, MoveAssignment)
{
    Array<int> array1;
    Array<int> array2;

    array1.add(50);
    array1.add(60);

    size_t size = array1.getSize();

    array2 = std::move(array1);

    EXPECT_EQ(array2.getSize(), size);
    EXPECT_EQ(array2[0], 50);
    EXPECT_EQ(array2[1], 60);
    EXPECT_EQ(array1.getSize(), 0);
}

// Тесты с фигурами
TEST(ArrayTest, WithFigures)
{
    Array<Figure<double> *> figures;

    auto rect = new Rectangle<double>(Point<double>(0, 0), Point<double>(4, 0),
                                      Point<double>(4, 3), Point<double>(0, 3));
    auto trap = new Trapezoid<double>(Point<double>(0, 0), Point<double>(4, 0),
                                      Point<double>(3, 2), Point<double>(1, 2));

    figures.add(rect);
    figures.add(trap);

    EXPECT_EQ(figures.getSize(), 2);

    // Очистка
    for (size_t i = 0; i < figures.getSize(); ++i)
    {
        delete figures[i];
    }
}

TEST(ArrayTest, WithRectangles)
{
    Array<Rectangle<int>> rectangles;

    Rectangle<int> r1(Point<int>(0, 0), Point<int>(4, 0),
                      Point<int>(4, 3), Point<int>(0, 3));
    Rectangle<int> r2(Point<int>(1, 1), Point<int>(5, 1),
                      Point<int>(5, 4), Point<int>(1, 4));

    rectangles.add(r1);
    rectangles.add(r2);

    EXPECT_EQ(rectangles.getSize(), 2);
    EXPECT_DOUBLE_EQ(rectangles[0].getArea(), 12.0);
}
