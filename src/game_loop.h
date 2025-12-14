#pragma once

#include <QTimer>

class Model;
class Arena;
class Snake;

class GameLoop : public QObject
{
Q_OBJECT

signals:
    void endGame();

public:
    explicit GameLoop(Model& model, int snakeMovementIntervalMs);
    void start();
    void stop();

private slots:
    void execute();

private:
    Model& model_;
    Arena& arena_;
    Snake& snake_;

    std::unique_ptr<QTimer> timer_;
};
