#include "gtest/gtest.h"
#include "collision_manager.h"
#include "arena.h"
#include "snake.h"

class SnakeCollisionWithWallTest : public testing::Test
{
protected:
    SnakeCollisionWithWallTest()
    {
        struct ArenaConfig
        {
            const int ROW_COUNT = 5;
            const int COLUMN_COUNT = 5;
        } arenaConfig;

        struct SnakeConfig
        {
            const Direction STARTING_DIRECTION = Direction::LEFT;
            const Coordinates STARTING_HEAD_COORDINATES{2, 2};
            const int STARTING_TOTAL_SEGMENT_COUNT = 3;
        } snakeConfig;

        arena_ = std::make_unique<Arena>(arenaConfig.ROW_COUNT, arenaConfig.COLUMN_COUNT);
        snake_ = std::make_unique<Snake>(gameConfig, snakeConfig.STARTING_HEAD_COORDINATES, snakeConfig.STARTING_DIRECTION, snakeConfig.STARTING_TOTAL_SEGMENT_COUNT);
    }

    GameConfig gameConfig;
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

    /* Now at 1,2 and moving left which means collision */
    EXPECT_TRUE(CollisionManager::checkSnakeCollisionWithArenaBoundary(*snake_, *arena_));
}
