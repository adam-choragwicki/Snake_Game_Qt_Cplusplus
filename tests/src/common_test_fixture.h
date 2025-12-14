#pragma once

#include "gtest/gtest.h"
#include "snake.h"
#include "config_test.h"

class CommonTestFixture : public testing::Test
{
public:
    CommonTestFixture()
    {
        const GenericTestConfig::Snake snakeConfig;
        snake_ = std::make_unique<Snake>(gameConfig_, snakeConfig.STARTING_HEAD_COORDINATES, snakeConfig.STARTING_DIRECTION, snakeConfig.STARTING_TOTAL_SEGMENT_COUNT);
    }

protected:
    GameConfig gameConfig_;
    std::unique_ptr<Snake> snake_;
};
