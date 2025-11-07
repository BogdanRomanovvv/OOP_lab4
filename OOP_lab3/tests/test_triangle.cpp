#include <gtest/gtest.h>
#include "Triangle.h"

// Тесты для класса Triangle

TEST(TriangleTest, DefaultConstructor)
{
    Triangle triangle;
    EXPECT_NO_THROW(triangle.getArea());
    EXPECT_GT(triangle.getArea(), 0.0);
}

TEST(TriangleTest, ParameterizedConstructor)
{
    Point p1(0, 0);
    Point p2(3, 0);
    Point p3(0, 4);

    Triangle triangle(p1, p2, p3);

    EXPECT_DOUBLE_EQ(triangle.getArea(), 6.0);
}

TEST(TriangleTest, InvalidTriangle)
{
    Point p1(0, 0);
    Point p2(1, 1);
    Point p3(2, 2); // Collinear points

    EXPECT_THROW(Triangle triangle(p1, p2, p3), std::invalid_argument);
}

TEST(TriangleTest, GetCenter)
{
    Point p1(0, 0);
    Point p2(3, 0);
    Point p3(0, 3);

    Triangle triangle(p1, p2, p3);
    Point center = triangle.getCenter();

    EXPECT_DOUBLE_EQ(center.x, 1.0);
    EXPECT_DOUBLE_EQ(center.y, 1.0);
}

TEST(TriangleTest, CopyConstructor)
{
    Point p1(0, 0);
    Point p2(4, 0);
    Point p3(0, 3);

    Triangle triangle1(p1, p2, p3);
    Triangle triangle2(triangle1);

    EXPECT_DOUBLE_EQ(triangle1.getArea(), triangle2.getArea());
    EXPECT_TRUE(triangle1 == triangle2);
}

TEST(TriangleTest, MoveConstructor)
{
    Point p1(0, 0);
    Point p2(4, 0);
    Point p3(0, 3);

    Triangle triangle1(p1, p2, p3);
    double area = triangle1.getArea();

    Triangle triangle2(std::move(triangle1));

    EXPECT_DOUBLE_EQ(triangle2.getArea(), area);
}

TEST(TriangleTest, CopyAssignment)
{
    Point p1(0, 0);
    Point p2(4, 0);
    Point p3(0, 3);

    Triangle triangle1(p1, p2, p3);
    Triangle triangle2;

    triangle2 = triangle1;

    EXPECT_TRUE(triangle1 == triangle2);
}

TEST(TriangleTest, MoveAssignment)
{
    Point p1(0, 0);
    Point p2(4, 0);
    Point p3(0, 3);

    Triangle triangle1(p1, p2, p3);
    double area = triangle1.getArea();

    Triangle triangle2;
    triangle2 = std::move(triangle1);

    EXPECT_DOUBLE_EQ(triangle2.getArea(), area);
}

TEST(TriangleTest, EqualityOperator)
{
    Point p1(0, 0);
    Point p2(4, 0);
    Point p3(0, 3);

    Triangle triangle1(p1, p2, p3);
    Triangle triangle2(p1, p2, p3);

    EXPECT_TRUE(triangle1 == triangle2);
}

TEST(TriangleTest, CastToDouble)
{
    Point p1(0, 0);
    Point p2(4, 0);
    Point p3(0, 3);

    Triangle triangle(p1, p2, p3);
    double area = static_cast<double>(triangle);

    EXPECT_DOUBLE_EQ(area, 6.0);
}

TEST(TriangleTest, Clone)
{
    Point p1(0, 0);
    Point p2(4, 0);
    Point p3(0, 3);

    Triangle triangle1(p1, p2, p3);
    auto cloned = triangle1.clone();

    EXPECT_DOUBLE_EQ(triangle1.getArea(), cloned->getArea());
}
