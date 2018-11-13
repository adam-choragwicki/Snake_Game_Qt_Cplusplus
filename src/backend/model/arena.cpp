#include "arena.h"
#include "config_prod.h"
#include "model/tiles/background_tiles/background_tile.h"

Arena::Arena(int horizontalSquaresCount, int verticalSquaresCount) : horizontalSquaresCount_(horizontalSquaresCount), verticalSquaresCount_(verticalSquaresCount)
{
    initializeBackground();
    initializeBoundaries();
}

void Arena::initializeBackground()
{
    auto addBackgroundTileType1 = [this](const Coordinates& coordinates)
    {
        const auto&[_, inserted] = backgroundTiles_.try_emplace(coordinates, std::make_unique<BackgroundTile1>(coordinates.x_, coordinates.y_));

        if(!inserted)
        {
            throw std::runtime_error("Error, trying to add duplicate coordinates to map");
        }
    };

    auto addBackgroundTileType2 = [this](const Coordinates& coordinates)
    {
        const auto&[_, inserted] = backgroundTiles_.try_emplace(coordinates, std::make_unique<BackgroundTile2>(coordinates.x_, coordinates.y_));

        if(!inserted)
        {
            throw std::runtime_error("Error, trying to add duplicate coordinates to map");
        }
    };

    for(int horizontalSquareIndex = 0; horizontalSquareIndex <= horizontalSquaresCount_; ++horizontalSquareIndex)
    {
        for(int verticalSquareIndex = 0; verticalSquareIndex <= verticalSquaresCount_; ++verticalSquareIndex)
        {
            Coordinates coordinates(horizontalSquareIndex, verticalSquareIndex);

            const bool columnEven = horizontalSquareIndex % 2 == 0;
            const bool rowEven = verticalSquareIndex % 2 == 0;

            if(columnEven)
            {
                if(rowEven)
                {
                    addBackgroundTileType1(coordinates);
                }
                else
                {
                    addBackgroundTileType2(coordinates);
                }
            }
            else
            {
                if(rowEven)
                {
                    addBackgroundTileType2(coordinates);
                }
                else
                {
                    addBackgroundTileType1(coordinates);
                }
            }
        }
    }
}

void Arena::initializeBoundaries()
{
    const int LEFT_BOUNDARY_X = 0;
    const int RIGHT_BOUNDARY_X = ConfigProd::Arena::TOTAL_HORIZONTAL_SQUARES_COUNT_INCLUDING_BOUNDARY_WALLS - 1;
    const int TOP_BOUNDARY_Y = 0;
    const int BOTTOM_BOUNDARY_Y = ConfigProd::Arena::TOTAL_VERTICAL_SQUARES_COUNT_INCLUDING_BOUNDARY_WALLS - 1;

    auto addArenaEdgeTile = [this](int x, int y)
    {
        Coordinates coordinates(x, y);

        auto[_, inserted] = boundaries_.try_emplace(coordinates, std::make_unique<Wall>(x, y));

        if(!inserted)
        {
            throw std::runtime_error("Error, adding duplicate arena edge tile at " + std::to_string(x) + "," + std::to_string(y));
        }
    };

    auto addArenaLeftEdge = [&addArenaEdgeTile]()
    {
        for(int y = TOP_BOUNDARY_Y; y <= BOTTOM_BOUNDARY_Y; ++y)
        {
            addArenaEdgeTile(LEFT_BOUNDARY_X, y);
        }
    };

    auto addArenaRightEdge = [&addArenaEdgeTile]()
    {
        for(int y = TOP_BOUNDARY_Y; y <= BOTTOM_BOUNDARY_Y; ++y)
        {
            addArenaEdgeTile(RIGHT_BOUNDARY_X, y);
        }
    };

    auto addArenaTopEdge = [&addArenaEdgeTile]()
    {
        for(int x = LEFT_BOUNDARY_X + 1; x < RIGHT_BOUNDARY_X; ++x)
        {
            addArenaEdgeTile(x, TOP_BOUNDARY_Y);
        }
    };

    auto addArenaBottomEdge = [&addArenaEdgeTile]()
    {
        for(int x = TOP_BOUNDARY_Y + 1; x < RIGHT_BOUNDARY_X; ++x)
        {
            addArenaEdgeTile(x, BOTTOM_BOUNDARY_Y);
        }
    };

    addArenaLeftEdge();
    addArenaRightEdge();
    addArenaTopEdge();
    addArenaBottomEdge();
}

[[maybe_unused]] void Arena::addAllPossibleSquares()
{
    const int MINIMUM_X = 0;
    const int MINIMUM_Y = 0;
    const int MAXIMUM_X = ConfigProd::Arena::TOTAL_HORIZONTAL_SQUARES_COUNT_INCLUDING_BOUNDARY_WALLS - 1;
    const int MAXIMUM_Y = ConfigProd::Arena::TOTAL_HORIZONTAL_SQUARES_COUNT_INCLUDING_BOUNDARY_WALLS - 1;

    auto addArenaEdgeTile = [this](int x, int y)
    {
        Coordinates coordinates(x, y);

        auto[_, inserted] = boundaries_.try_emplace(coordinates, std::make_unique<Wall>(x, y));

        if(!inserted)
        {
            throw std::runtime_error("Error, adding duplicate arena edge tile at " + std::to_string(x) + "," + std::to_string(y));
        }
    };

    for(int x = MINIMUM_X; x <= MAXIMUM_X; ++x)
    {
        for(int y = MINIMUM_Y; y <= MAXIMUM_Y; ++y)
        {
            addArenaEdgeTile(x, y);
        }
    }
}
