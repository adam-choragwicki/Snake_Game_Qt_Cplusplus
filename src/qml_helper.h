#pragma once

#include <QQmlApplicationEngine>
#include <QQuickWindow>

enum class QmlOverlay
{
    StartingImageOverlay,
    EndGameOverlay,
    EscapeMenuOverlay,
};

inline QString toString(const QmlOverlay overlay)
{
    switch (overlay)
    {
        case QmlOverlay::StartingImageOverlay: return "startingImageOverlay";
        case QmlOverlay::EndGameOverlay: return "endGameOverlay";
        case QmlOverlay::EscapeMenuOverlay: return "escapeMenuOverlay";
    }
    Q_UNREACHABLE();
}

class QmlHelper
{
public:
    explicit QmlHelper(QQmlApplicationEngine& view) : view_(view)
    {}

    QObject* getOverlay(QmlOverlay overlayEnum) const
    {
        QObject* root = getRootObject();

        auto overlay = root->findChild<QObject*>(toString(overlayEnum));
        if (!overlay)
        {
            const QString msg = QString("Overlay '%1' not found. It might not be defined in QML").arg(toString(overlayEnum));
            qCritical() << msg;
            throw std::runtime_error(msg.toStdString());
        }

        return overlay;
    }

    QQuickWindow* getMainWindow() const
    {
        QObject* root = getRootObject();

        auto window = qobject_cast<QQuickWindow*>(root);

        if (!window)
        {
            qCritical() << "Root object is not a QQuickWindow";
            throw std::runtime_error("Root object is not a QQuickWindow");
        }

        return window;
    }

    QObject* getGameInput() const
    {
        QObject* root = getRootObject();

        auto gameInput = root->findChild<QObject*>("gameInput");

        if (!gameInput)
        {
            qFatal("gameInput not found");
            throw std::runtime_error("gameInput not found");
        }

        return gameInput;
    }

    QObject* getSnakeLayer() const
    {
        QObject* root = getRootObject();

        auto snakeLayer = root->findChild<QObject*>("snakeLayer");

        if (!snakeLayer)
        {
            qFatal("snakeLayer not found");
            throw std::runtime_error("snakeLayer not found");
        }

        return snakeLayer;
    }

private:
    QQmlApplicationEngine& view_;

    QObject* getRootObject() const
    {
        if (view_.rootObjects().isEmpty())
        {
            qCritical() << "Root object not found";
            throw std::runtime_error("Root object not found");
        }

        QObject* root = view_.rootObjects().first();
        if (!root)
        {
            qCritical() << "Root object is nullptr";
            throw std::runtime_error("Root object is nullptr");
        }

        return root;
    }
};
