#include "model.h"

Model::Model(const GameConfig& gameConfig)
{
    qDebug() << "Initializing model";

    arena_ = std::make_unique<Arena>(gameConfig.arena().ROW_COUNT, gameConfig.arena().COLUMN_COUNT);

    snake_ = std::make_unique<Snake>(gameConfig,
                                     gameConfig.snake().STARTING_HEAD_COORDINATES,
                                     gameConfig.snake().STARTING_DIRECTION,
                                     gameConfig.snake().STARTING_TOTAL_SEGMENT_COUNT);

    snakeModel_ = std::make_unique<SnakeModel>(gameConfig, *snake_);

    foodManager_ = std::make_unique<FoodManager>(gameConfig, *snake_);
    foodModel_ = std::make_unique<FoodModel>(*foodManager_);

    scoreManager_ = std::make_unique<ScoreManager>();
}

void Model::reset()
{
    snake_->reset();
    scoreManager_->reset();
}
