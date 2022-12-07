#include "common_test_fixture.h"
#include "snake.h"

class SnakeTest : public CommonTestFixture
{
protected:
    SnakeTest()
    {
        snake_ = std::make_unique<Snake>();
    }

    ~SnakeTest()
    {
        snake_.reset();
    }

    std::unique_ptr<Snake> snake_;
};

TEST_F(SnakeTest, CreateSnake)
{
    auto& snakeSegments = snake_->getSegments();

    EXPECT_EQ(snakeSegments.size(), 3);
    EXPECT_EQ(snakeSegments.at(0)->getCoordinates(), Coordinates(20, 10));
    EXPECT_EQ(snakeSegments.at(1)->getCoordinates(), Coordinates(21, 10));
    EXPECT_EQ(snakeSegments.at(2)->getCoordinates(), Coordinates(22, 10));

    EXPECT_EQ(snake_->getDirection(), Direction::LEFT);
    EXPECT_EQ(snake_->getNextDirection(), Direction::LEFT);
}

TEST_F(SnakeTest, MoveSnake)
{
    auto& snakeSegments = snake_->getSegments();

    EXPECT_EQ(snake_->getDirection(), Direction::LEFT);
    EXPECT_EQ(snakeSegments.at(0)->getCoordinates(), Coordinates(20, 10));
    EXPECT_EQ(snakeSegments.at(1)->getCoordinates(), Coordinates(21, 10));
    EXPECT_EQ(snakeSegments.at(2)->getCoordinates(), Coordinates(22, 10));

    snake_->moveForward();

    EXPECT_EQ(snake_->getDirection(), Direction::LEFT);
    EXPECT_EQ(snakeSegments.at(0)->getCoordinates(), Coordinates(19, 10));
    EXPECT_EQ(snakeSegments.at(1)->getCoordinates(), Coordinates(20, 10));
    EXPECT_EQ(snakeSegments.at(2)->getCoordinates(), Coordinates(21, 10));

    snake_->setDirection(Direction::UP);
    snake_->moveForward();

    EXPECT_EQ(snake_->getDirection(), Direction::UP);
    EXPECT_EQ(snakeSegments.at(0)->getCoordinates(), Coordinates(19, 9));
    EXPECT_EQ(snakeSegments.at(1)->getCoordinates(), Coordinates(19, 10));
    EXPECT_EQ(snakeSegments.at(2)->getCoordinates(), Coordinates(20, 10));

    snake_->setDirection(Direction::RIGHT);
    snake_->moveForward();

    EXPECT_EQ(snake_->getDirection(), Direction::RIGHT);
    EXPECT_EQ(snakeSegments.at(0)->getCoordinates(), Coordinates(20, 9));
    EXPECT_EQ(snakeSegments.at(1)->getCoordinates(), Coordinates(19, 9));
    EXPECT_EQ(snakeSegments.at(2)->getCoordinates(), Coordinates(19, 10));

    snake_->setDirection(Direction::DOWN);
    snake_->moveForward();

    EXPECT_EQ(snake_->getDirection(), Direction::DOWN);
    EXPECT_EQ(snakeSegments.at(0)->getCoordinates(), Coordinates(20, 10));
    EXPECT_EQ(snakeSegments.at(1)->getCoordinates(), Coordinates(20, 9));
    EXPECT_EQ(snakeSegments.at(2)->getCoordinates(), Coordinates(19, 9));

    EXPECT_EQ(snakeSegments.size(), 3);
}

TEST_F(SnakeTest, GrowMechanism)
{
    auto& snakeSegments = snake_->getSegments();

    EXPECT_EQ(snake_->getDirection(), Direction::LEFT);
    EXPECT_EQ(snakeSegments.size(), 3);
    EXPECT_EQ(snakeSegments.at(0)->getCoordinates(), Coordinates(20, 10));
    EXPECT_EQ(snakeSegments.at(1)->getCoordinates(), Coordinates(21, 10));
    EXPECT_EQ(snakeSegments.at(2)->getCoordinates(), Coordinates(22, 10));

    snake_->processFoodEaten();

    EXPECT_EQ(snakeSegments.size(), 3);
    EXPECT_EQ(snakeSegments.at(0)->getCoordinates(), Coordinates(20, 10));
    EXPECT_EQ(snakeSegments.at(1)->getCoordinates(), Coordinates(21, 10));
    EXPECT_EQ(snakeSegments.at(2)->getCoordinates(), Coordinates(22, 10));

    snake_->moveForward();

    EXPECT_EQ(snakeSegments.size(), 3);
    EXPECT_EQ(snakeSegments.at(0)->getCoordinates(), Coordinates(19, 10));
    EXPECT_EQ(snakeSegments.at(1)->getCoordinates(), Coordinates(20, 10));
    EXPECT_EQ(snakeSegments.at(2)->getCoordinates(), Coordinates(21, 10));

    snake_->moveForward();

    EXPECT_EQ(snakeSegments.size(), 3);
    EXPECT_EQ(snakeSegments.at(0)->getCoordinates(), Coordinates(18, 10));
    EXPECT_EQ(snakeSegments.at(1)->getCoordinates(), Coordinates(19, 10));
    EXPECT_EQ(snakeSegments.at(2)->getCoordinates(), Coordinates(20, 10));

    /*Here 3-segment long snake grows 3 moves after eating food*/
    snake_->moveForward();

    EXPECT_EQ(snakeSegments.size(), 4);
    EXPECT_EQ(snakeSegments.at(0)->getCoordinates(), Coordinates(17, 10));
    EXPECT_EQ(snakeSegments.at(1)->getCoordinates(), Coordinates(18, 10));
    EXPECT_EQ(snakeSegments.at(2)->getCoordinates(), Coordinates(19, 10));
    EXPECT_EQ(snakeSegments.at(3)->getCoordinates(), Coordinates(20, 10));

    snake_->moveForward();

    EXPECT_EQ(snakeSegments.size(), 4);
    EXPECT_EQ(snakeSegments.at(0)->getCoordinates(), Coordinates(16, 10));
    EXPECT_EQ(snakeSegments.at(1)->getCoordinates(), Coordinates(17, 10));
    EXPECT_EQ(snakeSegments.at(2)->getCoordinates(), Coordinates(18, 10));
    EXPECT_EQ(snakeSegments.at(3)->getCoordinates(), Coordinates(19, 10));
}

TEST_F(SnakeTest, SnakeHeadPositiom)
{
    EXPECT_EQ(snake_->getHeadCoordinates(), snake_->getSegments().at(0)->getCoordinates());

    snake_->moveForward();
    snake_->moveForward();
    snake_->moveForward();

    EXPECT_EQ(snake_->getHeadCoordinates(), snake_->getSegments().at(0)->getCoordinates());
}
