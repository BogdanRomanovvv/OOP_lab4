#include <gtest/gtest.h>
#include "Trapezoid.h"
#include <cmath>

// Тесты для Trapezoid<double>
class TrapezoidTest : public ::testing::Test
{
protected:
    const double EPSILON = 1e-6;
};

TEST_F(TrapezoidTest, ConstructorAndGetters)
{
    // Трапеция, вписанная в круг (координаты подобраны так, чтобы все точки были примерно на одинаковом расстоянии от центра)
    Trapezoid<double> trap(Point<double>(0, 0), Point<double>(4, 0),
                           Point<double>(3, 2), Point<double>(1, 2));

    EXPECT_NEAR(trap.getVertex(0).x, 0, EPSILON);
    EXPECT_NEAR(trap.getVertex(0).y, 0, EPSILON);
}

TEST_F(TrapezoidTest, Area)
{
    Trapezoid<double> trap(Point<double>(0, 0), Point<double>(4, 0),
                           Point<double>(3, 2), Point<double>(1, 2));

    double area = trap.getArea();
    // Площадь трапеции по формуле Гаусса
    EXPECT_NEAR(area, 6.0, EPSILON);
}

TEST_F(TrapezoidTest, Center)
{
    Trapezoid<double> trap(Point<double>(0, 0), Point<double>(4, 0),
                           Point<double>(3, 2), Point<double>(1, 2));

    Point<double> center = trap.getCenter();
    EXPECT_NEAR(center.x, 2.0, EPSILON);
    EXPECT_NEAR(center.y, 1.0, EPSILON);
}

TEST_F(TrapezoidTest, CopyConstructor)
{
    Trapezoid<double> trap1(Point<double>(0, 0), Point<double>(4, 0),
                            Point<double>(3, 2), Point<double>(1, 2));
    Trapezoid<double> trap2(trap1);

    EXPECT_TRUE(trap1 == trap2);
    EXPECT_NEAR(trap2.getArea(), trap1.getArea(), EPSILON);
}

TEST_F(TrapezoidTest, MoveConstructor)
{
    Trapezoid<double> trap1(Point<double>(0, 0), Point<double>(4, 0),
                            Point<double>(3, 2), Point<double>(1, 2));
    double area1 = trap1.getArea();

    Trapezoid<double> trap2(std::move(trap1));
    EXPECT_NEAR(trap2.getArea(), area1, EPSILON);
}

TEST_F(TrapezoidTest, OperatorDouble)
{
    Trapezoid<double> trap(Point<double>(0, 0), Point<double>(4, 0),
                           Point<double>(3, 2), Point<double>(1, 2));

    double area = static_cast<double>(trap);
    EXPECT_NEAR(area, 6.0, EPSILON);
}

TEST_F(TrapezoidTest, Clone)
{
    Trapezoid<double> trap(Point<double>(0, 0), Point<double>(4, 0),
                           Point<double>(3, 2), Point<double>(1, 2));

    auto cloned = trap.clone();
    EXPECT_NEAR(cloned->getArea(), trap.getArea(), EPSILON);
    EXPECT_TRUE(trap.equals(*cloned));
}

TEST_F(TrapezoidTest, IntegerCoordinates)
{
    Trapezoid<int> trap(Point<int>(0, 0), Point<int>(4, 0),
                        Point<int>(3, 2), Point<int>(1, 2));

    EXPECT_EQ(trap.getVertex(0).x, 0);
    EXPECT_EQ(trap.getVertex(0).y, 0);
    EXPECT_NEAR(trap.getArea(), 6.0, EPSILON);
}
