#include "gtest/gtest.h"
#include "model/snake.h"

class SnakeMovementTest : public ::testing::Test
{
protected:
    Snake snake_;
};

TEST_F(SnakeMovementTest, MoveInStraightLineOneTime)
{
    snake_.moveForward();

    EXPECT_EQ(snake_.length(), 5);

    EXPECT_EQ(snake_.getSegmentAt(0).getCoordinates(), Coordinates({19, 10}));
    EXPECT_EQ(snake_.getSegmentAt(1).getCoordinates(), Coordinates({20, 10}));
    EXPECT_EQ(snake_.getSegmentAt(2).getCoordinates(), Coordinates({21, 10}));
    EXPECT_EQ(snake_.getSegmentAt(3).getCoordinates(), Coordinates({22, 10}));
    EXPECT_EQ(snake_.getSegmentAt(4).getCoordinates(), Coordinates({23, 10}));

    EXPECT_EQ(snake_.getSegmentAt(0).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(1).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(2).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(3).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(4).getMovementDirection(), Direction::LEFT);
}

TEST_F(SnakeMovementTest, MoveInStraightLineTwoTimes)
{
    snake_.moveForward();
    snake_.moveForward();

    EXPECT_EQ(snake_.length(), 5);

    EXPECT_EQ(snake_.getSegmentAt(0).getCoordinates(), Coordinates({18, 10}));
    EXPECT_EQ(snake_.getSegmentAt(1).getCoordinates(), Coordinates({19, 10}));
    EXPECT_EQ(snake_.getSegmentAt(2).getCoordinates(), Coordinates({20, 10}));
    EXPECT_EQ(snake_.getSegmentAt(3).getCoordinates(), Coordinates({21, 10}));
    EXPECT_EQ(snake_.getSegmentAt(4).getCoordinates(), Coordinates({22, 10}));

    EXPECT_EQ(snake_.getSegmentAt(0).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(1).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(2).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(3).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(4).getMovementDirection(), Direction::LEFT);
}

TEST_F(SnakeMovementTest, SetNextHeadDirection)
{
    /*Same as MoveInStraightLineTwoTimes, nothing is supposed to change until next move forward after changing next head direction*/

    snake_.moveForward();
    snake_.moveForward();
    snake_.setNextHeadDirection(Direction::DOWN);

    EXPECT_EQ(snake_.length(), 5);

    EXPECT_EQ(snake_.getSegmentAt(0).getCoordinates(), Coordinates({18, 10}));
    EXPECT_EQ(snake_.getSegmentAt(1).getCoordinates(), Coordinates({19, 10}));
    EXPECT_EQ(snake_.getSegmentAt(2).getCoordinates(), Coordinates({20, 10}));
    EXPECT_EQ(snake_.getSegmentAt(3).getCoordinates(), Coordinates({21, 10}));
    EXPECT_EQ(snake_.getSegmentAt(4).getCoordinates(), Coordinates({22, 10}));

    EXPECT_EQ(snake_.getSegmentAt(0).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(1).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(2).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(3).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(4).getMovementDirection(), Direction::LEFT);
}

TEST_F(SnakeMovementTest, SetNextHeadDirectionAndMoveInOldDirection)
{
    /*After setting next head direction snake still moves in old direction but after the move the new direction is set*/
    snake_.moveForward();
    snake_.moveForward();
    snake_.setNextHeadDirection(Direction::DOWN);
    snake_.moveForward();

    EXPECT_EQ(snake_.length(), 5);

    EXPECT_EQ(snake_.getSegmentAt(0).getCoordinates(), Coordinates({17, 10}));
    EXPECT_EQ(snake_.getSegmentAt(1).getCoordinates(), Coordinates({18, 10}));
    EXPECT_EQ(snake_.getSegmentAt(2).getCoordinates(), Coordinates({19, 10}));
    EXPECT_EQ(snake_.getSegmentAt(3).getCoordinates(), Coordinates({20, 10}));
    EXPECT_EQ(snake_.getSegmentAt(4).getCoordinates(), Coordinates({21, 10}));

    EXPECT_EQ(snake_.getSegmentAt(0).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(1).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(2).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(3).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(4).getMovementDirection(), Direction::LEFT);
}

TEST_F(SnakeMovementTest, MoveInNewDirection)
{
    snake_.moveForward();
    snake_.moveForward();
    snake_.setNextHeadDirection(Direction::DOWN);
    snake_.moveForward();
    snake_.moveForward();

    EXPECT_EQ(snake_.length(), 5);

    EXPECT_EQ(snake_.getSegmentAt(0).getCoordinates(), Coordinates({17, 11}));
    EXPECT_EQ(snake_.getSegmentAt(1).getCoordinates(), Coordinates({17, 10}));
    EXPECT_EQ(snake_.getSegmentAt(2).getCoordinates(), Coordinates({18, 10}));
    EXPECT_EQ(snake_.getSegmentAt(3).getCoordinates(), Coordinates({19, 10}));
    EXPECT_EQ(snake_.getSegmentAt(4).getCoordinates(), Coordinates({20, 10}));

    EXPECT_EQ(snake_.getSegmentAt(0).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(1).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(2).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(3).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(4).getMovementDirection(), Direction::LEFT);
}

TEST_F(SnakeMovementTest, MoveInNewDirectionTwoTimes)
{
    snake_.moveForward();
    snake_.moveForward();
    snake_.setNextHeadDirection(Direction::DOWN);
    snake_.moveForward();
    snake_.moveForward();
    snake_.moveForward();

    EXPECT_EQ(snake_.length(), 5);

    EXPECT_EQ(snake_.getSegmentAt(0).getCoordinates(), Coordinates({17, 12}));
    EXPECT_EQ(snake_.getSegmentAt(1).getCoordinates(), Coordinates({17, 11}));
    EXPECT_EQ(snake_.getSegmentAt(2).getCoordinates(), Coordinates({17, 10}));
    EXPECT_EQ(snake_.getSegmentAt(3).getCoordinates(), Coordinates({18, 10}));
    EXPECT_EQ(snake_.getSegmentAt(4).getCoordinates(), Coordinates({19, 10}));

    EXPECT_EQ(snake_.getSegmentAt(0).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(1).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(2).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(3).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(4).getMovementDirection(), Direction::LEFT);
}

TEST_F(SnakeMovementTest, SetNextHeadDirectionAgain)
{
    /*Same as MoveInNewDirectionTwoTimes, nothing is supposed to change until next move forward after changing next head direction*/
    snake_.moveForward();
    snake_.moveForward();
    snake_.setNextHeadDirection(Direction::DOWN);
    snake_.moveForward();
    snake_.moveForward();
    snake_.moveForward();
    snake_.setNextHeadDirection(Direction::RIGHT);

    EXPECT_EQ(snake_.length(), 5);

    EXPECT_EQ(snake_.getSegmentAt(0).getCoordinates(), Coordinates({17, 12}));
    EXPECT_EQ(snake_.getSegmentAt(1).getCoordinates(), Coordinates({17, 11}));
    EXPECT_EQ(snake_.getSegmentAt(2).getCoordinates(), Coordinates({17, 10}));
    EXPECT_EQ(snake_.getSegmentAt(3).getCoordinates(), Coordinates({18, 10}));
    EXPECT_EQ(snake_.getSegmentAt(4).getCoordinates(), Coordinates({19, 10}));

    EXPECT_EQ(snake_.getSegmentAt(0).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(1).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(2).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(3).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_.getSegmentAt(4).getMovementDirection(), Direction::LEFT);
}

TEST_F(SnakeMovementTest, SetNextHeadDirectionAndMoveInOldDirectionAgain)
{
    /*After setting next head direction snake still moves in old direction but after the move the new direction is set*/
    snake_.moveForward();
    snake_.moveForward();
    snake_.setNextHeadDirection(Direction::DOWN);
    snake_.moveForward();
    snake_.moveForward();
    snake_.moveForward();
    snake_.setNextHeadDirection(Direction::RIGHT);
    snake_.moveForward();

    EXPECT_EQ(snake_.length(), 5);

    EXPECT_EQ(snake_.getSegmentAt(0).getCoordinates(), Coordinates({17, 13}));
    EXPECT_EQ(snake_.getSegmentAt(1).getCoordinates(), Coordinates({17, 12}));
    EXPECT_EQ(snake_.getSegmentAt(2).getCoordinates(), Coordinates({17, 11}));
    EXPECT_EQ(snake_.getSegmentAt(3).getCoordinates(), Coordinates({17, 10}));
    EXPECT_EQ(snake_.getSegmentAt(4).getCoordinates(), Coordinates({18, 10}));

    EXPECT_EQ(snake_.getSegmentAt(0).getMovementDirection(), Direction::RIGHT);
    EXPECT_EQ(snake_.getSegmentAt(1).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(2).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(3).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(4).getMovementDirection(), Direction::LEFT);
}

TEST_F(SnakeMovementTest, SetNextHeadDirectionAndMoveInNewDirectionAgain)
{
    snake_.moveForward();
    snake_.moveForward();
    snake_.setNextHeadDirection(Direction::DOWN);
    snake_.moveForward();
    snake_.moveForward();
    snake_.moveForward();
    snake_.setNextHeadDirection(Direction::RIGHT);
    snake_.moveForward();
    snake_.moveForward();

    EXPECT_EQ(snake_.length(), 5);

    EXPECT_EQ(snake_.getSegmentAt(0).getCoordinates(), Coordinates({18, 13}));
    EXPECT_EQ(snake_.getSegmentAt(1).getCoordinates(), Coordinates({17, 13}));
    EXPECT_EQ(snake_.getSegmentAt(2).getCoordinates(), Coordinates({17, 12}));
    EXPECT_EQ(snake_.getSegmentAt(3).getCoordinates(), Coordinates({17, 11}));
    EXPECT_EQ(snake_.getSegmentAt(4).getCoordinates(), Coordinates({17, 10}));

    EXPECT_EQ(snake_.getSegmentAt(0).getMovementDirection(), Direction::RIGHT);
    EXPECT_EQ(snake_.getSegmentAt(1).getMovementDirection(), Direction::RIGHT);
    EXPECT_EQ(snake_.getSegmentAt(2).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(3).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_.getSegmentAt(4).getMovementDirection(), Direction::DOWN);
}

TEST_F(SnakeMovementTest, SnakeMovementDirectionIsAlwaysEqualToHeadMovementDirection)
{
    EXPECT_EQ(snake_.getHead().getMovementDirection(), snake_.getMovementDirection());
    snake_.moveForward();
    EXPECT_EQ(snake_.getHead().getMovementDirection(), snake_.getMovementDirection());
    snake_.moveForward();
    EXPECT_EQ(snake_.getHead().getMovementDirection(), snake_.getMovementDirection());
    snake_.setNextHeadDirection(Direction::DOWN);
    EXPECT_EQ(snake_.getHead().getMovementDirection(), snake_.getMovementDirection());
    snake_.moveForward();
    EXPECT_EQ(snake_.getHead().getMovementDirection(), snake_.getMovementDirection());
    snake_.moveForward();
    EXPECT_EQ(snake_.getHead().getMovementDirection(), snake_.getMovementDirection());
    snake_.moveForward();
    EXPECT_EQ(snake_.getHead().getMovementDirection(), snake_.getMovementDirection());
    snake_.setNextHeadDirection(Direction::RIGHT);
    EXPECT_EQ(snake_.getHead().getMovementDirection(), snake_.getMovementDirection());
    snake_.moveForward();
    EXPECT_EQ(snake_.getHead().getMovementDirection(), snake_.getMovementDirection());
    snake_.moveForward();
    EXPECT_EQ(snake_.getHead().getMovementDirection(), snake_.getMovementDirection());
}
