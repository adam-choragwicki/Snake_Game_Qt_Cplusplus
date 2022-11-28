#pragma once

#include "snake.h"
#include "food.h"
#include "speed_manager.h"
#include "common.h"

#include <QTimer>

class Model : public QObject
{
Q_OBJECT

public:
    explicit Model();

    [[nodiscard]] Snake* getSnake() const
    { return snake_.get(); }

    [[nodiscard]] Food* getFood() const
    { return food_.get(); }

    GameState getGameState() const
    { return gameState_; }

    void setGameState(GameState gameState)
    { gameState_ = gameState; }

    void reset();
    void generateFood();

private:
    std::unique_ptr<Snake> snake_;
    std::unique_ptr<Food> food_;

    GameState gameState_;
};
