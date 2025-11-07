#include <gtest/gtest.h>
#include "Octagon.h"

// Тесты для класса Octagon

TEST(OctagonTest, DefaultConstructor)
{
    Octagon octagon;
    EXPECT_NO_THROW(octagon.getArea());
    EXPECT_GT(octagon.getArea(), 0.0);
}

TEST(OctagonTest, GetCenter)
{
    Octagon octagon;
    Point center = octagon.getCenter();

    // Для правильного восьмиугольника с центром в (0,0)
    EXPECT_NEAR(center.x, 0.0, 1e-9);
    EXPECT_NEAR(center.y, 0.0, 1e-9);
}

TEST(OctagonTest, CopyConstructor)
{
    Octagon octagon1;
    Octagon octagon2(octagon1);

    EXPECT_DOUBLE_EQ(octagon1.getArea(), octagon2.getArea());
    EXPECT_TRUE(octagon1 == octagon2);
}

TEST(OctagonTest, MoveConstructor)
{
    Octagon octagon1;
    double area = octagon1.getArea();

    Octagon octagon2(std::move(octagon1));

    EXPECT_DOUBLE_EQ(octagon2.getArea(), area);
}

TEST(OctagonTest, CopyAssignment)
{
    Octagon octagon1;
    Octagon octagon2;

    // Создаем разные октагоны
    Point p1(0, 0), p2(1, 0), p3(2, 1), p4(2, 2);
    Point p5(1, 3), p6(0, 3), p7(-1, 2), p8(-1, 1);

    try
    {
        octagon2 = Octagon(p1, p2, p3, p4, p5, p6, p7, p8);
    }
    catch (...)
    {
        // Если валидация не проходит, используем дефолтный
    }

    octagon2 = octagon1;

    EXPECT_TRUE(octagon1 == octagon2);
}

TEST(OctagonTest, EqualityOperator)
{
    Octagon octagon1;
    Octagon octagon2;

    EXPECT_TRUE(octagon1 == octagon2);
}

TEST(OctagonTest, CastToDouble)
{
    Octagon octagon;
    double area = static_cast<double>(octagon);

    EXPECT_GT(area, 0.0);
    EXPECT_DOUBLE_EQ(area, octagon.getArea());
}

TEST(OctagonTest, Clone)
{
    Octagon octagon1;
    auto cloned = octagon1.clone();

    EXPECT_DOUBLE_EQ(octagon1.getArea(), cloned->getArea());
}

TEST(OctagonTest, GetTypeName)
{
    Octagon octagon;
    EXPECT_STREQ(octagon.getTypeName(), "Octagon");
}
