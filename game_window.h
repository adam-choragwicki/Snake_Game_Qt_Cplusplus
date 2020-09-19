#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>

#include <snake.h>
#include <food.h>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void InitializeGameplayScene();

private:
    Ui::GameWindow* m_pUi;
    QGraphicsScene m_Scene;
    QTimer m_GameTickTimer;
    Snake m_Snake;
    Food m_Food;

    void DrawAllSquares();
    void DrawGameArena();
    void StartGame();
    void CheckSnakeCollisionWithWall();
    void CheckSnakeCollisionWithFoodSquare();
    void CheckSnakeCollisionWithItself();
    void RedrawSnake();
    void SetGameSpeedLevel(int speedLevel);

    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void GameTick();
    void on_m_SpeedHorizontalSlider_valueChanged(int value);
};
