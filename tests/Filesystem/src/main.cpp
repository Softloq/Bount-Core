#include <gtest/gtest.h>

import Bount.Filesystem;

int add(int a, int b);

TEST(AdditionTest, PositiveNumbers)
{
    EXPECT_EQ(add(2, 4), 5);
}

TEST(SubtractinTest, PositiveNumbers)
{
    EXPECT_EQ(add(2, -4), -2);
}

int add(int a, int b) {
    return a + b;
}