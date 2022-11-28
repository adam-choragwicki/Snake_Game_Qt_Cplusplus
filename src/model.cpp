#include "model.h"

Model::Model()
{
    snake_ = std::make_unique<Snake>();
    generateFood();
    gameState_ = GameState::STOPPED;
}

void Model::reset()
{
    snake_ = std::make_unique<Snake>();
    generateFood();
    gameState_ = GameState::STOPPED;
}

void Model::generateFood()
{
    food_ = std::make_unique<Food>();
}
