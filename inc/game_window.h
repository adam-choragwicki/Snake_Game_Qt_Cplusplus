#pragma once

#include "game_engine.h"
#include "food.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QGraphicsScene>

namespace Ui
{
    class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget* parent = nullptr);
    ~GameWindow() override;

private:
    void initializeGameplayAreaScene();
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    Ui::GameWindow* ui_;
    QGraphicsScene scene_;
    std::unique_ptr<GameEngine> gameEngine_;

private slots:
    void dialogRestartGameSlot();
    void speedSliderValueChangedSlot();
};
