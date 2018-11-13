#include "common_test_fixture.h"

class SnakeGrowthTest : public CommonTestFixture
{
};

TEST_F(SnakeGrowthTest, GrowInStraightLineOnce)
{
    EXPECT_EQ(snake_->length(), 3);

    snake_->eatFood();

    EXPECT_EQ(snake_->length(), 3);

    snake_->grow();

    EXPECT_EQ(snake_->length(), 4);
}

TEST_F(SnakeGrowthTest, GrowInStraightLineTwice)
{
    EXPECT_EQ(snake_->length(), 3);

    snake_->eatFood();

    EXPECT_EQ(snake_->length(), 3);

    snake_->grow();

    EXPECT_EQ(snake_->length(), 4);

    snake_->eatFood();

    EXPECT_EQ(snake_->length(), 4);

    snake_->grow();

    EXPECT_EQ(snake_->length(), 5);
}
