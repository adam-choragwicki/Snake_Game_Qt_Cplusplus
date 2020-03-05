#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>

#include <snake.h>
#include <drawer.h>
#include <food.h>

namespace Ui {
class MainWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private:
    Ui::MainWindow* m_pUi;
    QGraphicsScene* m_pScene;

    QTimer* m_pUpdaterTimer;
    Drawer* m_pDrawer;
    Snake* m_pSnake;
    Food *m_pFood;

    void DrawAllSquares();
    void DrawGameArena();
    void RestartGame();

    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void GameTick();
};
