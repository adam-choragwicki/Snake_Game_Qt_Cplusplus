#pragma once

#include "game_engine.h"
#include "food.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QGraphicsScene>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(GameEngine& gameEngine, QWidget* parent = nullptr);
    ~GameWindow() override;

    void initializeGameplayAreaScene();

private:
    Ui::GameWindow* ui_;
    GameEngine& gameEngine_;
    QGraphicsScene scene_;

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void dialogRestartGameSlot();

private slots:
    void speedSliderValueChangedSlot();
};
