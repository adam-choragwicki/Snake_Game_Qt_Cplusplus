#pragma once

#include "snake.h"
#include "food_factory.h"
#include "food_manager.h"
#include "arena.h"
#include "food_model.h"
#include "score_manager.h"
#include "snake_model.h"

class Model : public QObject
{
public:
    explicit Model(const GameConfig& gameConfig);
    void reset();

    [[nodiscard]] Arena& getArena() const { return *arena_; }

    [[nodiscard]] Snake& getSnake() const { return *snake_; }
    [[nodiscard]] SnakeModel& getSnakeModel() const { return *snakeModel_; }

    [[nodiscard]] FoodManager& getFoodManager() const { return *foodManager_; }
    FoodModel& getFoodModel() const { return *foodModel_; }

    [[nodiscard]] ScoreManager& getScoreManager() const { return *scoreManager_; }

private:
    std::unique_ptr<Arena> arena_;
    std::unique_ptr<Snake> snake_;
    std::unique_ptr<SnakeModel> snakeModel_;

    std::unique_ptr<FoodManager> foodManager_;
    std::unique_ptr<FoodModel> foodModel_;

    std::unique_ptr<ScoreManager> scoreManager_;
};
