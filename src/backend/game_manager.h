#pragma once

#include <QObject>

class Model;
class GameLoop;

class GameManager : public QObject
{
Q_OBJECT

public slots:
    void processRestartGameRequest();
    void endGame();

public:
    explicit GameManager(Model& model);

    [[nodiscard]] bool isRunning() const
    { return gameState_ == GameState::RUNNING; }

    [[nodiscard]] bool isReadyToStart() const
    { return gameState_ == GameState::READY_TO_START; }

    [[nodiscard]] bool isStopped() const
    { return gameState_ == GameState::STOPPED; }

    void prepareGameToStart();

    void setGameLoop(GameLoop* gameLoop)
    { gameLoop_ = gameLoop; }

    void startGame();

private:

    enum class GameState
    {
        BEFORE_FIRST_RUN, READY_TO_START, RUNNING, STOPPED
    } gameState_;

    GameLoop* gameLoop_{};

    Model& model_;
};
