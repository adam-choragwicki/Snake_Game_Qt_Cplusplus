#pragma once

#include "gtest/gtest.h"
#include "model/snake.h"
#include "config_test.h"

class CommonTestFixture : public ::testing::Test
{
public:
    CommonTestFixture()
    {
        GenericTestConfig::Snake snakeConfig;
        snake_ = std::make_unique<Snake>(snakeConfig.STARTING_HEAD_COORDINATES, snakeConfig.STARTING_DIRECTION, snakeConfig.STARTING_TOTAL_SEGMENT_COUNT, nullptr);
    }

protected:
    std::unique_ptr<Snake> snake_;
};
