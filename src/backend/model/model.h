#pragma once

#include "snake.h"
#include "food.h"
#include "game_speed_manager.h"
#include "food_factory.h"
#include "game_state_manager.h"
#include "food_manager.h"

#include <QTimer>

class Model : public QObject
{
Q_OBJECT

public:
    Model();
    void reset();

    [[nodiscard]] Snake& getSnake() const
    { return *snake_; }

    GameStateManager& getGameStateManager()
    { return *gameStateManager_; }

    GameSpeedManager& getGameSpeedManager()
    { return gameSpeedManager_; }

    [[nodiscard]] const QTimer& getGameTickTimer() const
    { return gameTickTimer_; }

    [[nodiscard]] const FoodManager& getFoodManager() const
    { return *foodManager_; }

    [[nodiscard]] FoodManager& getFoodManager()
    { return *foodManager_; }

private:
    QTimer gameTickTimer_;

    std::unique_ptr<Snake> snake_;
    std::unique_ptr<FoodManager> foodManager_;
    std::unique_ptr<GameStateManager> gameStateManager_;

    GameSpeedManager gameSpeedManager_;
};
