#include "common_test_fixture.h"
#include "coordinates.h"
#include "head_segment.h"

class SnakeMovementTest : public CommonTestFixture
{
};

TEST_F(SnakeMovementTest, MoveInStraightLineOneTime)
{
    snake_->moveForward();

    EXPECT_EQ(snake_->length(), 3);

    EXPECT_EQ(snake_->getSegmentAt(0).getCoordinates(), Coordinates({9, 10}));
    EXPECT_EQ(snake_->getSegmentAt(1).getCoordinates(), Coordinates({10, 10}));
    EXPECT_EQ(snake_->getSegmentAt(2).getCoordinates(), Coordinates({11, 10}));

    EXPECT_EQ(snake_->getSegmentAt(0).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_->getSegmentAt(1).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_->getSegmentAt(2).getMovementDirection(), Direction::LEFT);
}

TEST_F(SnakeMovementTest, MoveInStraightLineTwoTimes)
{
    snake_->moveForward();
    snake_->moveForward();

    EXPECT_EQ(snake_->length(), 3);

    EXPECT_EQ(snake_->getSegmentAt(0).getCoordinates(), Coordinates({8, 10}));
    EXPECT_EQ(snake_->getSegmentAt(1).getCoordinates(), Coordinates({9, 10}));
    EXPECT_EQ(snake_->getSegmentAt(2).getCoordinates(), Coordinates({10, 10}));

    EXPECT_EQ(snake_->getSegmentAt(0).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_->getSegmentAt(1).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_->getSegmentAt(2).getMovementDirection(), Direction::LEFT);
}

TEST_F(SnakeMovementTest, SetNextHeadDirection)
{
    snake_->moveForward();
    snake_->moveForward();

    snake_->setNextHeadDirection(Direction::DOWN);
    snake_->updateMovementDirection();

    EXPECT_EQ(snake_->length(), 3);

    EXPECT_EQ(snake_->getSegmentAt(0).getCoordinates(), Coordinates({8, 10}));
    EXPECT_EQ(snake_->getSegmentAt(1).getCoordinates(), Coordinates({9, 10}));
    EXPECT_EQ(snake_->getSegmentAt(2).getCoordinates(), Coordinates({10, 10}));

    EXPECT_EQ(snake_->getSegmentAt(0).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_->getSegmentAt(1).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_->getSegmentAt(2).getMovementDirection(), Direction::LEFT);
}

TEST_F(SnakeMovementTest, SetNextHeadDirectionAndMoveInNewDirection)
{
    snake_->moveForward();
    snake_->moveForward();

    snake_->setNextHeadDirection(Direction::DOWN);
    snake_->updateMovementDirection();

    snake_->moveForward();

    EXPECT_EQ(snake_->length(), 3);

    EXPECT_EQ(snake_->getSegmentAt(0).getCoordinates(), Coordinates({8, 11}));
    EXPECT_EQ(snake_->getSegmentAt(1).getCoordinates(), Coordinates({8, 10}));
    EXPECT_EQ(snake_->getSegmentAt(2).getCoordinates(), Coordinates({9, 10}));

    EXPECT_EQ(snake_->getSegmentAt(0).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_->getSegmentAt(1).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_->getSegmentAt(2).getMovementDirection(), Direction::LEFT);
}

TEST_F(SnakeMovementTest, MoveInNewDirectionTwice)
{
    snake_->moveForward();
    snake_->moveForward();

    snake_->setNextHeadDirection(Direction::DOWN);
    snake_->updateMovementDirection();

    snake_->moveForward();
    snake_->moveForward();

    EXPECT_EQ(snake_->length(), 3);

    EXPECT_EQ(snake_->getSegmentAt(0).getCoordinates(), Coordinates({8, 12}));
    EXPECT_EQ(snake_->getSegmentAt(1).getCoordinates(), Coordinates({8, 11}));
    EXPECT_EQ(snake_->getSegmentAt(2).getCoordinates(), Coordinates({8, 10}));

    EXPECT_EQ(snake_->getSegmentAt(0).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_->getSegmentAt(1).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_->getSegmentAt(2).getMovementDirection(), Direction::DOWN);
}

TEST_F(SnakeMovementTest, MoveInNewDirectionThrice)
{
    snake_->moveForward();
    snake_->moveForward();

    snake_->setNextHeadDirection(Direction::DOWN);
    snake_->updateMovementDirection();

    snake_->moveForward();
    snake_->moveForward();
    snake_->moveForward();

    EXPECT_EQ(snake_->length(), 3);

    EXPECT_EQ(snake_->getSegmentAt(0).getCoordinates(), Coordinates({8, 13}));
    EXPECT_EQ(snake_->getSegmentAt(1).getCoordinates(), Coordinates({8, 12}));
    EXPECT_EQ(snake_->getSegmentAt(2).getCoordinates(), Coordinates({8, 11}));

    EXPECT_EQ(snake_->getSegmentAt(0).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_->getSegmentAt(1).getMovementDirection(), Direction::DOWN);
    EXPECT_EQ(snake_->getSegmentAt(2).getMovementDirection(), Direction::DOWN);
}

TEST_F(SnakeMovementTest, SnakeMovementDirectionIsAlwaysEqualToHeadMovementDirection)
{
    EXPECT_EQ(snake_->getHead().getMovementDirection(), snake_->getMovementDirection());
    snake_->moveForward();
    EXPECT_EQ(snake_->getHead().getMovementDirection(), snake_->getMovementDirection());
    snake_->moveForward();
    EXPECT_EQ(snake_->getHead().getMovementDirection(), snake_->getMovementDirection());
    snake_->setNextHeadDirection(Direction::DOWN);
    EXPECT_EQ(snake_->getHead().getMovementDirection(), snake_->getMovementDirection());
    snake_->moveForward();
    EXPECT_EQ(snake_->getHead().getMovementDirection(), snake_->getMovementDirection());
    snake_->moveForward();
    EXPECT_EQ(snake_->getHead().getMovementDirection(), snake_->getMovementDirection());
    snake_->moveForward();
    EXPECT_EQ(snake_->getHead().getMovementDirection(), snake_->getMovementDirection());
    snake_->setNextHeadDirection(Direction::RIGHT);
    EXPECT_EQ(snake_->getHead().getMovementDirection(), snake_->getMovementDirection());
    snake_->moveForward();
    EXPECT_EQ(snake_->getHead().getMovementDirection(), snake_->getMovementDirection());
    snake_->moveForward();
    EXPECT_EQ(snake_->getHead().getMovementDirection(), snake_->getMovementDirection());
}
