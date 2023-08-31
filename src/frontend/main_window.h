#pragma once

#include <QMainWindow>
#include <QKeyEvent>
#include <QSlider>
#include "game_arena.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

signals:
    void keyPressedEvent(QKeyEvent* event);
    void keyReleasedEvent(QKeyEvent* event);
    void newGameRequest();
    void applicationTerminationRequest();

public slots:
    void showEndGameDialog();

public:
    explicit MainWindow(const Model& model);
    ~MainWindow() override;

    [[nodiscard]] QSlider* getSpeedSlider() const;

private:
    void closeEvent(QCloseEvent*) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void centerOnScreen();

    Ui::MainWindow* ui_;
    std::unique_ptr<GameArena> gameArena_;
};
