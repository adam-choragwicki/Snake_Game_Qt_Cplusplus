#include "game.h"
#include <QQmlContext>
#include "direction.h"

Game::Game()
{
    printAppInfo();

    gameConfig_ = std::make_unique<GameConfig>();

    model_ = std::make_unique<Model>(*gameConfig_);
    view_ = std::make_unique<QQmlApplicationEngine>();
    controller_ = std::make_unique<Controller>(*gameConfig_, *model_, *view_);

    exposeDataToQml();

    initializeQmlEngine();

    connect(controller_.get(),
            &Controller::applicationShutdownRequested,
            this,
            []()
            {
                QMetaObject::invokeMethod(QCoreApplication::instance(),
                                          []()
                                          {
                                              QCoreApplication::quit();
                                          },
                                          Qt::QueuedConnection);
            });

    connect(QCoreApplication::instance(),
            &QCoreApplication::aboutToQuit,
            []()
            {
                // TODO Future cleanup (save configs, close files, etc.)
                qInfo() << "Exiting application";
            });
}

void Game::printAppInfo()
{
    qInfo() << "Application version:" << APP_VERSION;
    qInfo() << "Qt version:" << QT_VERSION_STR;
    qInfo() << "Build type:" << BUILD_TYPE;

#if defined(Q_OS_WIN)
    qInfo() << "OS: Windows";
#elif defined(Q_OS_LINUX)
    qInfo() << "OS: Linux";
#endif
}

void Game::exposeDataToQml() const
{
    // expose constants
    view_->rootContext()->setContextProperty(QStringLiteral("baseSquareSize"), gameConfig_->arena().BASE_SQUARE_SIZE);
    view_->rootContext()->setContextProperty(QStringLiteral("snakeMovementIntervalMs"), gameConfig_->SNAKE_MOVEMENT_INTERVAL_MS);
    view_->rootContext()->setContextProperty(QStringLiteral("totalRowCountIncludingBoundaryWalls"), gameConfig_->arena().TOTAL_ROW_COUNT_INCLUDING_BOUNDARY_WALLS);
    view_->rootContext()->setContextProperty(QStringLiteral("totalColumnCountIncludingBoundaryWalls"), gameConfig_->arena().TOTAL_COLUMN_COUNT_INCLUDING_BOUNDARY_WALLS);

    // expose models
    view_->rootContext()->setContextProperty(QStringLiteral("snakeModel"), &model_->getSnakeModel());
    view_->rootContext()->setContextProperty(QStringLiteral("foodModel"), &model_->getFoodModel());

    qmlRegisterUncreatableType<DirectionQml>("CustomEnums", 1, 0, "Direction", "Enum only for QML");
}

void Game::initializeQmlEngine()
{
    view_->rootContext()->setContextProperty("Controller", controller_.get());

    /*
     * Rationale for the below QML setup:
     * - QQmlApplicationEngine::load() is effectively asynchronous; rootObjects() may be empty immediately.
     * - We rely on objectCreated() as the reliable success/failure notification.
     * - On failure we queue QCoreApplication::exit(1) (via a queued invoke) so the exit code is honored even
     *   if this runs before the event loop starts. Calling exit/quit directly here can be ignored otherwise.
     * - Qt::SingleShotConnection ensures the handler runs exactly once (avoids double-calls on reloads).
     */
    connect(view_.get(),
            &QQmlApplicationEngine::objectCreated,
            controller_.get(),
            [this](QObject* obj, const QUrl& url)
            {
                if (!obj)
                {
                    qCritical() << "QML root creation failed for" << url;

                    QMetaObject::invokeMethod(QCoreApplication::instance(),
                                              []()
                                              {
                                                  QCoreApplication::exit(1);
                                              },
                                              Qt::QueuedConnection);

                    return;
                }

                controller_->onQmlEngineFullyInitialized();
            },
            Qt::SingleShotConnection);

    view_->loadFromModule("SnakeQml", "Main");
}
