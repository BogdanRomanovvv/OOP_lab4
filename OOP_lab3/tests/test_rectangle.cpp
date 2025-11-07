#include <gtest/gtest.h>
#include "Rectangle.h"
#include <cmath>

// Тесты для Rectangle<double>
class RectangleTest : public ::testing::Test
{
protected:
    const double EPSILON = 1e-6;
};

TEST_F(RectangleTest, ConstructorAndGetters)
{
    Rectangle<double> rect(Point<double>(0, 0), Point<double>(4, 0),
                           Point<double>(4, 3), Point<double>(0, 3));

    EXPECT_NEAR(rect.getVertex(0).x, 0, EPSILON);
    EXPECT_NEAR(rect.getVertex(0).y, 0, EPSILON);
    EXPECT_NEAR(rect.getVertex(2).x, 4, EPSILON);
    EXPECT_NEAR(rect.getVertex(2).y, 3, EPSILON);
}

TEST_F(RectangleTest, Area)
{
    Rectangle<double> rect(Point<double>(0, 0), Point<double>(4, 0),
                           Point<double>(4, 3), Point<double>(0, 3));

    double area = rect.getArea();
    EXPECT_NEAR(area, 12.0, EPSILON); // 4 * 3 = 12
}

TEST_F(RectangleTest, Center)
{
    Rectangle<double> rect(Point<double>(0, 0), Point<double>(4, 0),
                           Point<double>(4, 3), Point<double>(0, 3));

    Point<double> center = rect.getCenter();
    EXPECT_NEAR(center.x, 2.0, EPSILON);
    EXPECT_NEAR(center.y, 1.5, EPSILON);
}

TEST_F(RectangleTest, CopyConstructor)
{
    Rectangle<double> rect1(Point<double>(0, 0), Point<double>(4, 0),
                            Point<double>(4, 3), Point<double>(0, 3));
    Rectangle<double> rect2(rect1);

    EXPECT_TRUE(rect1 == rect2);
    EXPECT_NEAR(rect2.getArea(), rect1.getArea(), EPSILON);
}

TEST_F(RectangleTest, MoveConstructor)
{
    Rectangle<double> rect1(Point<double>(0, 0), Point<double>(4, 0),
                            Point<double>(4, 3), Point<double>(0, 3));
    double area1 = rect1.getArea();

    Rectangle<double> rect2(std::move(rect1));
    EXPECT_NEAR(rect2.getArea(), area1, EPSILON);
}

TEST_F(RectangleTest, OperatorDouble)
{
    Rectangle<double> rect(Point<double>(0, 0), Point<double>(4, 0),
                           Point<double>(4, 3), Point<double>(0, 3));

    double area = static_cast<double>(rect);
    EXPECT_NEAR(area, 12.0, EPSILON);
}

TEST_F(RectangleTest, Clone)
{
    Rectangle<double> rect(Point<double>(0, 0), Point<double>(4, 0),
                           Point<double>(4, 3), Point<double>(0, 3));

    auto cloned = rect.clone();
    EXPECT_NEAR(cloned->getArea(), rect.getArea(), EPSILON);
    EXPECT_TRUE(rect.equals(*cloned));
}

TEST_F(RectangleTest, IntegerCoordinates)
{
    Rectangle<int> rect(Point<int>(0, 0), Point<int>(4, 0),
                        Point<int>(4, 3), Point<int>(0, 3));

    EXPECT_EQ(rect.getVertex(0).x, 0);
    EXPECT_EQ(rect.getVertex(0).y, 0);
    EXPECT_NEAR(rect.getArea(), 12.0, EPSILON);
}

TEST_F(RectangleTest, InvalidRectangle)
{
    // Попытка создать невалидный прямоугольник (не перпендикулярные стороны)
    EXPECT_THROW(
        Rectangle<double>(Point<double>(0, 0), Point<double>(4, 1),
                          Point<double>(3, 4), Point<double>(0, 3)),
        std::invalid_argument);
}
