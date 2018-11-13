#pragma once

#include <QMainWindow>
#include <QKeyEvent>
#include "graphics_view.h"

class Model;

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
    ~MainWindow() override = default;

    void updateViewport();

    [[nodiscard]] QTimer* getViewportUpdateTimer() const
    { return viewportUpdateTimer_.get(); }

private:
    void closeEvent(QCloseEvent*) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void centerOnScreen(QScreen* screen);
    void centerOnPrimaryScreen();

    const Model& model_;

    std::unique_ptr<GraphicsView> graphicsView_;

    std::unique_ptr<QTimer> viewportUpdateTimer_;

    static constexpr auto VIEWPORT_UPDATE_INTERVAL = std::chrono::milliseconds(17);
};
