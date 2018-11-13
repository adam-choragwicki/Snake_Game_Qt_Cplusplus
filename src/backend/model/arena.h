#pragma once

#include "coordinates.h"
#include "tiles/background_tiles/abstract_background_tile.h"
#include "tiles/wall.h"

class Arena
{
public:
    Arena(int horizontalSquaresCount, int verticalSquaresCount);

    [[nodiscard]] const std::map<Coordinates, std::unique_ptr<Wall>>& getBoundaries() const
    { return boundaries_; }

    [[nodiscard]] const std::map<Coordinates, std::unique_ptr<AbstractBackgroundTile>>& getBackgroundTiles() const
    { return backgroundTiles_; }

    [[nodiscard]] int getMinimumX() const
    { return MINIMUM_X; }

    [[nodiscard]] int getMinimumY() const
    { return MINIMUM_Y; }

    [[nodiscard]] int getMaximumX() const
    { return MAXIMUM_X; }

    [[nodiscard]] int getMaximumY() const
    { return MAXIMUM_Y; }

private:
    void initializeBackground();
    void initializeBoundaries();
    [[maybe_unused]] void addAllPossibleSquares();

    const int horizontalSquaresCount_;
    const int verticalSquaresCount_;

    const int MINIMUM_X = 1;
    const int MINIMUM_Y = 1;
    const int MAXIMUM_X = horizontalSquaresCount_;
    const int MAXIMUM_Y = verticalSquaresCount_;

    std::map<Coordinates, std::unique_ptr<Wall>> boundaries_;
    std::map<Coordinates, std::unique_ptr<AbstractBackgroundTile>> backgroundTiles_;
};
