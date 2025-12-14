#pragma once

class Arena
{
public:
    Arena(int rowCount, int columnCount);

    [[nodiscard]] constexpr int getMinimumX() const { return MINIMUM_X; }
    [[nodiscard]] constexpr int getMinimumY() const { return MINIMUM_Y; }

    [[nodiscard]] constexpr int getMaximumX() const { return MAXIMUM_X; }
    [[nodiscard]] constexpr int getMaximumY() const { return MAXIMUM_Y; }

private:
    const int rowCount_;
    const int columnCount_;

    const int MINIMUM_X = 1;
    const int MINIMUM_Y = 1;
    const int MAXIMUM_X = columnCount_;
    const int MAXIMUM_Y = rowCount_;
};
