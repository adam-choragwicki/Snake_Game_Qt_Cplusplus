#include "gtest/gtest.h"
#include "model/snake.h"
#include "collision_detector.h"

class SnakeCollisionWithWallTest : public ::testing::Test
{
protected:
    Snake snake_;
};

TEST_F(SnakeCollisionWithWallTest, SnakeCollidesWithWall)
{
    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_FALSE(CollisionDetector::checkSnakeCollisionWithWall(snake_));

    snake_.moveForward();

    EXPECT_TRUE(CollisionDetector::checkSnakeCollisionWithWall(snake_));
}
