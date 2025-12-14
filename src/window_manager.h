#pragma once

#include <QQuickWindow>

class WindowManager
{
public:
    explicit WindowManager();

    void setWindow(QQuickWindow* window);

    [[nodiscard]] bool isStartInFullScreenEnabled() const { return startInFullScreenEnabled_; }
    [[nodiscard]] QSize getInitialRenderResolution() const { return initialRenderResolution_; }

    void toggleFullScreen();

    void setResolutionHD();
    void setResolutionFullHD();
    void setResolutionQHD();
    void setResolutionUHD();

private:
    QSize determineInitialRenderResolution();
    void setResolution(QSize resolution);

    QWindow* window_{};

    const bool startInFullScreenEnabled_ = true;

    // Render resolution — can change depending on platform/settings
    const QSize initialRenderResolution_;
};
