#include "common_test_fixture.h"
#include "coordinates.h"

class SnakeCreationTest : public CommonTestFixture
{
};

TEST_F(SnakeCreationTest, CreateSnake)
{
    EXPECT_EQ(snake_->length(), 3);

    EXPECT_EQ(snake_->getSegmentAt(0).getCoordinates(), Coordinates({10, 10}));
    EXPECT_EQ(snake_->getSegmentAt(1).getCoordinates(), Coordinates({11, 10}));
    EXPECT_EQ(snake_->getSegmentAt(2).getCoordinates(), Coordinates({12, 10}));

    EXPECT_EQ(snake_->getSegmentAt(0).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_->getSegmentAt(1).getMovementDirection(), Direction::LEFT);
    EXPECT_EQ(snake_->getSegmentAt(2).getMovementDirection(), Direction::LEFT);

    EXPECT_EQ(snake_->getHeadCoordinates(), Coordinates({10, 10}));
    EXPECT_EQ(snake_->getMovementDirection(), Direction::LEFT);
}
