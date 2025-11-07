#include <gtest/gtest.h>
#include "Rhombus.h"
#include <cmath>

// Тесты для Rhombus<double>
class RhombusTest : public ::testing::Test
{
protected:
    const double EPSILON = 1e-6;
};

TEST_F(RhombusTest, ConstructorAndGetters)
{
    Rhombus<double> rhomb(Point<double>(3, 0), Point<double>(6, 2),
                          Point<double>(3, 4), Point<double>(0, 2));

    EXPECT_NEAR(rhomb.getVertex(0).x, 3, EPSILON);
    EXPECT_NEAR(rhomb.getVertex(0).y, 0, EPSILON);
}

TEST_F(RhombusTest, Area)
{
    Rhombus<double> rhomb(Point<double>(3, 0), Point<double>(6, 2),
                          Point<double>(3, 4), Point<double>(0, 2));

    double area = rhomb.getArea();
    // Площадь ромба: d1 * d2 / 2
    // d1 = расстояние от (3,0) до (3,4) = 4
    // d2 = расстояние от (6,2) до (0,2) = 6
    // Площадь = 4 * 6 / 2 = 12
    EXPECT_NEAR(area, 12.0, EPSILON);
}

TEST_F(RhombusTest, Center)
{
    Rhombus<double> rhomb(Point<double>(3, 0), Point<double>(6, 2),
                          Point<double>(3, 4), Point<double>(0, 2));

    Point<double> center = rhomb.getCenter();
    EXPECT_NEAR(center.x, 3.0, EPSILON);
    EXPECT_NEAR(center.y, 2.0, EPSILON);
}

TEST_F(RhombusTest, CopyConstructor)
{
    Rhombus<double> rhomb1(Point<double>(3, 0), Point<double>(6, 2),
                           Point<double>(3, 4), Point<double>(0, 2));
    Rhombus<double> rhomb2(rhomb1);

    EXPECT_TRUE(rhomb1 == rhomb2);
    EXPECT_NEAR(rhomb2.getArea(), rhomb1.getArea(), EPSILON);
}

TEST_F(RhombusTest, MoveConstructor)
{
    Rhombus<double> rhomb1(Point<double>(3, 0), Point<double>(6, 2),
                           Point<double>(3, 4), Point<double>(0, 2));
    double area1 = rhomb1.getArea();

    Rhombus<double> rhomb2(std::move(rhomb1));
    EXPECT_NEAR(rhomb2.getArea(), area1, EPSILON);
}

TEST_F(RhombusTest, OperatorDouble)
{
    Rhombus<double> rhomb(Point<double>(3, 0), Point<double>(6, 2),
                          Point<double>(3, 4), Point<double>(0, 2));

    double area = static_cast<double>(rhomb);
    EXPECT_NEAR(area, 12.0, EPSILON);
}

TEST_F(RhombusTest, Clone)
{
    Rhombus<double> rhomb(Point<double>(3, 0), Point<double>(6, 2),
                          Point<double>(3, 4), Point<double>(0, 2));

    auto cloned = rhomb.clone();
    EXPECT_NEAR(cloned->getArea(), rhomb.getArea(), EPSILON);
    EXPECT_TRUE(rhomb.equals(*cloned));
}

TEST_F(RhombusTest, IntegerCoordinates)
{
    Rhombus<int> rhomb(Point<int>(3, 0), Point<int>(6, 2),
                       Point<int>(3, 4), Point<int>(0, 2));

    EXPECT_EQ(rhomb.getVertex(0).x, 3);
    EXPECT_EQ(rhomb.getVertex(0).y, 0);
    EXPECT_NEAR(rhomb.getArea(), 12.0, EPSILON);
}

TEST_F(RhombusTest, InvalidRhombus)
{
    // Попытка создать невалидный ромб (не все стороны равны)
    EXPECT_THROW(
        Rhombus<double>(Point<double>(0, 0), Point<double>(4, 0),
                        Point<double>(5, 2), Point<double>(1, 2)),
        std::invalid_argument);
}
