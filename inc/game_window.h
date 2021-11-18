#pragma once

#include "snake.h"
#include "food.h"

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget* parent = nullptr);
    ~GameWindow();

    void initializeGameplayAreaScene();

private:
    Ui::GameWindow* ui_;
    QGraphicsScene scene_;
    QTimer gameTickTimer_;
    Snake snake_;
    Food food_;

    void drawAllSquares();
    void drawGameArena();
    void startGame();
    void checkSnakeCollisionWithWall();
    void checkSnakeCollisionWithFoodSquare();
    void checkSnakeCollisionWithItself();
    void redrawSnake();
    void setGameSpeedLevel(int speedLevel);
    void activateSpeedBoost();
    void dectivateSpeedBoost();

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void dialogRestartGame();

private slots:
    void gameTick();
    void on_m_SpeedHorizontalSlider_valueChanged(int value);
};
