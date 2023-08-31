#include "gtest/gtest.h"
#include "model/snake.h"
#include "collision_detector.h"
class SnakeCollisionWithItselfTest : public ::testing::Test
{
protected:
    Snake snake_;
};

TEST_F(SnakeCollisionWithItselfTest, SnakeCollidesWithItself)
{
    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithItself(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithItself(snake_));

    snake_.setNextHeadDirection(Direction::DOWN);

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithItself(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithItself(snake_));

    snake_.setNextHeadDirection(Direction::RIGHT);

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithItself(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithItself(snake_));

    snake_.setNextHeadDirection(Direction::UP);

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithItself(snake_));

    snake_.moveForward();

    EXPECT_TRUE(CollisionDetector::checkSnakeCollisionWithItself(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithItself(snake_));
}
