#pragma once

#include "coordinates.h"
#include "game_config.h"
#include <vector>

class Snake;

class FoodFactory
{
public:
    FoodFactory(const GameConfig& config, const Snake& snake);

    Coordinates generateNewCoordinates() const;

private:
    std::vector<Coordinates> generateAllTiles() const;

    const GameConfig& config_;
    const Snake& snake_;
    std::vector<Coordinates> allCoordinates_;
};
