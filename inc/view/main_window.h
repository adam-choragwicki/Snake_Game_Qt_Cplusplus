#pragma once

#include "ui_main_window.h"
#include "game_arena.h"

#include <QKeyEvent>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

signals:
    void keyPressedEvent(Key key);
    void speedBoostKeyReleasedEvent();
    void restartEvent();

public slots:
    void processGameEndEvent(GameResult gameResult);

public:
    explicit MainWindow(Model* model);
    ~MainWindow() override = default;

    [[nodiscard]] QSlider* getSpeedSlider() const
    { return ui_->speed_Slider; }

    [[nodiscard]] GameArena* getGameArena() const
    { return gameArena_.get(); }

private:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    std::unique_ptr<Ui::MainWindow> ui_;
    std::unique_ptr<GameArena> gameArena_;
};
