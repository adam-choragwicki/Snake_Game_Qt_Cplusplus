#include "gtest/gtest.h"
#include "model/snake.h"
#include "collision_manager.h"

class SnakeCollisionWithItselfTest : public ::testing::Test
{
protected:
    SnakeCollisionWithItselfTest()
    {
        struct SnakeConfig
        {
            const Direction STARTING_DIRECTION = Direction::LEFT;
            const Coordinates STARTING_HEAD_COORDINATES{10, 10};
            const int STARTING_TOTAL_SEGMENT_COUNT = 5;
        } snakeConfig;

        snake_ = std::make_unique<Snake>(snakeConfig.STARTING_HEAD_COORDINATES, snakeConfig.STARTING_DIRECTION, snakeConfig.STARTING_TOTAL_SEGMENT_COUNT, nullptr);
    }

protected:
    std::unique_ptr<Snake> snake_;
};

TEST_F(SnakeCollisionWithItselfTest, SnakeCollidesWithItself)
{
    EXPECT_FALSE(CollisionManager::checkSnakeCollisionWithItself(*snake_));

    snake_->moveForward();

    EXPECT_FALSE(CollisionManager::checkSnakeCollisionWithItself(*snake_));

    snake_->setNextHeadDirection(Direction::DOWN);
    snake_->updateMovementDirection();

    EXPECT_FALSE(CollisionManager::checkSnakeCollisionWithItself(*snake_));

    snake_->moveForward();

    EXPECT_FALSE(CollisionManager::checkSnakeCollisionWithItself(*snake_));

    snake_->setNextHeadDirection(Direction::RIGHT);
    snake_->updateMovementDirection();

    EXPECT_FALSE(CollisionManager::checkSnakeCollisionWithItself(*snake_));

    snake_->moveForward();

    EXPECT_FALSE(CollisionManager::checkSnakeCollisionWithItself(*snake_));

    snake_->setNextHeadDirection(Direction::UP);
    snake_->updateMovementDirection();

    EXPECT_TRUE(CollisionManager::checkSnakeCollisionWithItself(*snake_));
}
