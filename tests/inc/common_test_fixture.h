#pragma once

#include "gtest/gtest.h"

class CommonTestFixture : public ::testing::Test
{
protected:
    void SetUp() override;
    void TearDown() override;
};