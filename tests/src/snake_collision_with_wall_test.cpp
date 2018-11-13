#include "gtest/gtest.h"
#include "collision_manager.h"
#include "model/arena.h"
#include "model/snake.h"

class SnakeCollisionWithWallTest : public ::testing::Test
{
protected:
    SnakeCollisionWithWallTest()
    {
        struct ArenaConfig
        {
            const int PLAYABLE_HORIZONTAL_SQUARES_COUNT = 5;
            const int PLAYABLE_VERTICAL_SQUARES_COUNT = 5;
        } arenaConfig;

        struct SnakeConfig
        {
            const Direction STARTING_DIRECTION = Direction::LEFT;
            const Coordinates STARTING_HEAD_COORDINATES{2, 2};
            const int STARTING_TOTAL_SEGMENT_COUNT = 3;
        } snakeConfig;

        arena_ = std::make_unique<Arena>(arenaConfig.PLAYABLE_HORIZONTAL_SQUARES_COUNT, arenaConfig.PLAYABLE_VERTICAL_SQUARES_COUNT);
        snake_ = std::make_unique<Snake>(snakeConfig.STARTING_HEAD_COORDINATES, snakeConfig.STARTING_DIRECTION, snakeConfig.STARTING_TOTAL_SEGMENT_COUNT, nullptr);
    }

protected:
    std::unique_ptr<Arena> arena_;
    std::unique_ptr<Snake> snake_;
};

TEST_F(SnakeCollisionWithWallTest, SnakeCollidesWithLeftWall)
{
    /* Starting at 2,2 */
    EXPECT_FALSE(CollisionManager::checkSnakeCollisionWithArenaBoundary(*snake_, *arena_));

    /* Now at 2,2 */
    snake_->moveForward();
    /* Now at 1,2 */

    /* Now at 1,2 and moving left so collision */
    EXPECT_TRUE(CollisionManager::checkSnakeCollisionWithArenaBoundary(*snake_, *arena_));
}
