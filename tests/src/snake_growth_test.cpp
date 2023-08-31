#include "gtest/gtest.h"
#include "model/snake.h"

class SnakeGrowthTest : public ::testing::Test
{
protected:
    Snake snake_;
};

TEST_F(SnakeGrowthTest, GrowInStraightLineOnce)
{
    EXPECT_EQ(snake_.length(), 5);

    snake_.eatFood();

    EXPECT_EQ(snake_.length(), 5);

    snake_.moveForward();

    EXPECT_EQ(snake_.length(), 6);
}

TEST_F(SnakeGrowthTest, GrowInStraightLineTwice)
{
    EXPECT_EQ(snake_.length(), 5);

    snake_.eatFood();

    EXPECT_EQ(snake_.length(), 5);

    snake_.moveForward();

    EXPECT_EQ(snake_.length(), 6);

    snake_.eatFood();

    EXPECT_EQ(snake_.length(), 6);

    snake_.moveForward();

    EXPECT_EQ(snake_.length(), 7);
}
