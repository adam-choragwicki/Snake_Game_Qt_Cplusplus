#pragma once

#include <QObject>
#include <QTimer>

class Model;

class Arena;
class Snake;
class GameManager;

class GameLoop : public QObject
{
Q_OBJECT

signals:
    void endGame();

public:
    explicit GameLoop(Model& model);
    void start();
    void stop();

private slots:
    void execute();

private:
    Model& model_;

    Arena& arena_;
    Snake& snake_;

    std::unique_ptr<QTimer> gameLoopTimer_;

    bool newFoodPosition{};
};
