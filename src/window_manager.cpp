#include "window_manager.h"
#include "resolution.h"
#include <QWindow>
#include <QDebug>

WindowManager::WindowManager() : initialRenderResolution_(determineInitialRenderResolution())
{}

void WindowManager::setWindow(QQuickWindow* window)
{
    if (window)
    {
        window_ = window;
        // qDebug() << "WindowManager attached to QQuickWindow";
    }
    else
    {
        throw std::runtime_error("WindowManager::setWindow() called with nullptr");
    }
}

void WindowManager::toggleFullScreen()
{
    if (!window_)
    {
        throw std::runtime_error("WindowManager::toggleFullScreen() called before window was set");
    }

    const bool isCurrentlyFullscreen = window_->windowState() & Qt::WindowFullScreen;

    if (isCurrentlyFullscreen)
    {
        window_->showNormal();
        // qDebug() << "Exited fullscreen mode";
    }
    else
    {
        window_->showFullScreen();
        // qDebug() << "Entered fullscreen mode";
    }
}

void WindowManager::setResolution(const QSize resolution)
{
    if (!window_)
    {
        throw std::runtime_error("WindowManager::setResolution() called before window was set");
    }

    window_->showNormal();
    window_->resize(resolution);
    window_->setPosition(QGuiApplication::primaryScreen()->geometry().center() - QPoint(resolution.width() / 2, resolution.height() / 2));

    // qDebug() << "Resolution set to" << resolution.width() << "x" << resolution.height();
}

QSize WindowManager::determineInitialRenderResolution()
{
    // try to detect primary screen resolution
    if (const QScreen* screen = QGuiApplication::primaryScreen())
    {
        const QSize screenResolution = screen->size();
        qDebug() << "Detected primary screen resolution:" << screenResolution.width() << "x" << screenResolution.height();
        return screenResolution;
    }

    // fallback
    qWarning() << "Failed to detect primary screen resolution. Using fallback:" << Resolution::FullHD.width() << "x" << Resolution::FullHD.height();
    return Resolution::FullHD;
}

void WindowManager::setResolutionHD()
{
    setResolution(Resolution::HD);
}

void WindowManager::setResolutionFullHD()
{
    setResolution(Resolution::FullHD);
}

void WindowManager::setResolutionQHD()
{
    setResolution(Resolution::QHD);
}

void WindowManager::setResolutionUHD()
{
    setResolution(Resolution::UHD);
}
