#include "gtest/gtest.h"
#include "model/snake.h"

class SnakeCreationTest : public ::testing::Test
{
protected:
    Snake snake_;
};

TEST_F(SnakeCreationTest, CreateSnake)
{
    EXPECT_EQ(snake_.length(), 5);

    EXPECT_EQ(snake_.getSegmentAt(0).getCoordinates(), Coordinates({20, 10}));
    EXPECT_EQ(snake_.getSegmentAt(1).getCoordinates(), Coordinates({21, 10}));
    EXPECT_EQ(snake_.getSegmentAt(2).getCoordinates(), Coordinates({22, 10}));
    EXPECT_EQ(snake_.getSegmentAt(3).getCoordinates(), Coordinates({23, 10}));
    EXPECT_EQ(snake_.getSegmentAt(4).getCoordinates(), Coordinates({24, 10}));

    EXPECT_EQ(snake_.getSegmentAt(0).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(1).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(2).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(3).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(4).getMovementDirection(), Direction::LEFT);

    EXPECT_EQ(snake_.getHeadCoordinates(), Coordinates({20, 10}));
    EXPECT_EQ(snake_.getMovementDirection(), Direction::LEFT);
}
