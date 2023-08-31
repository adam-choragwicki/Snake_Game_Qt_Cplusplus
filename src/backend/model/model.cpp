#include "model.h"

Model::Model() : gameSpeedManager_(gameTickTimer_)
{
    reset();
}

void Model::reset()
{
    snake_ = std::make_unique<Snake>();
    foodManager_ = std::make_unique<FoodManager>(*snake_);
    gameStateManager_ = std::make_unique<GameStateManager>(gameSpeedManager_, gameTickTimer_);
}
