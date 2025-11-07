#include <gtest/gtest.h>
#include "Square.h"

// Тесты для класса Square

TEST(SquareTest, DefaultConstructor)
{
    Square square;
    EXPECT_NO_THROW(square.getArea());
    EXPECT_DOUBLE_EQ(square.getArea(), 1.0);
}

TEST(SquareTest, ParameterizedConstructor)
{
    Point p1(0, 0);
    Point p2(2, 0);
    Point p3(2, 2);
    Point p4(0, 2);

    Square square(p1, p2, p3, p4);

    EXPECT_DOUBLE_EQ(square.getArea(), 4.0);
}

TEST(SquareTest, InvalidSquare)
{
    Point p1(0, 0);
    Point p2(1, 0);
    Point p3(2, 1);
    Point p4(1, 1); // Not a square

    EXPECT_THROW(Square square(p1, p2, p3, p4), std::invalid_argument);
}

TEST(SquareTest, GetCenter)
{
    Point p1(0, 0);
    Point p2(2, 0);
    Point p3(2, 2);
    Point p4(0, 2);

    Square square(p1, p2, p3, p4);
    Point center = square.getCenter();

    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(SquareTest, CopyConstructor)
{
    Point p1(0, 0);
    Point p2(3, 0);
    Point p3(3, 3);
    Point p4(0, 3);

    Square square1(p1, p2, p3, p4);
    Square square2(square1);

    EXPECT_DOUBLE_EQ(square1.getArea(), square2.getArea());
    EXPECT_TRUE(square1 == square2);
}

TEST(SquareTest, MoveConstructor)
{
    Point p1(0, 0);
    Point p2(3, 0);
    Point p3(3, 3);
    Point p4(0, 3);

    Square square1(p1, p2, p3, p4);
    double area = square1.getArea();

    Square square2(std::move(square1));

    EXPECT_DOUBLE_EQ(square2.getArea(), area);
}

TEST(SquareTest, CopyAssignment)
{
    Point p1(0, 0);
    Point p2(3, 0);
    Point p3(3, 3);
    Point p4(0, 3);

    Square square1(p1, p2, p3, p4);
    Square square2;

    square2 = square1;

    EXPECT_TRUE(square1 == square2);
}

TEST(SquareTest, EqualityOperator)
{
    Point p1(0, 0);
    Point p2(2, 0);
    Point p3(2, 2);
    Point p4(0, 2);

    Square square1(p1, p2, p3, p4);
    Square square2(p1, p2, p3, p4);

    EXPECT_TRUE(square1 == square2);
}

TEST(SquareTest, CastToDouble)
{
    Point p1(0, 0);
    Point p2(2, 0);
    Point p3(2, 2);
    Point p4(0, 2);

    Square square(p1, p2, p3, p4);
    double area = static_cast<double>(square);

    EXPECT_DOUBLE_EQ(area, 4.0);
}
