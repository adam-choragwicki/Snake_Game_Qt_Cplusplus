#include "main_window.h"
#include "model/model.h"
#include "end_game_dialog.h"
#include "config_prod.h"
#include "spdlog/spdlog.h"
#include <QGuiApplication>

MainWindow::MainWindow(const Model& model) : QMainWindow(), model_(model)
{
    spdlog::debug("Initializing view");

    setWindowTitle("Snake");
    setFocus(Qt::ActiveWindowFocusReason);

    graphicsView_ = std::make_unique<GraphicsView>(model_.getScene(), this);

    /* Arbitrary size modifier to avoid scrollbars */
    const int ARBITRARY_WINDOW_SIZE_MODIFIER = 2;

    const int WINDOW_WIDTH = ConfigProd::Arena::TOTAL_HORIZONTAL_SQUARES_COUNT_INCLUDING_BOUNDARY_WALLS * ConfigProd::Arena::PRIMARY_SQUARE_SIZE + ARBITRARY_WINDOW_SIZE_MODIFIER;
    const int WINDOW_HEIGHT = ConfigProd::Arena::TOTAL_VERTICAL_SQUARES_COUNT_INCLUDING_BOUNDARY_WALLS * ConfigProd::Arena::PRIMARY_SQUARE_SIZE + ARBITRARY_WINDOW_SIZE_MODIFIER;

    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    setPalette(QPalette(Qt::black));

    setCentralWidget(graphicsView_.get());

    centerOnPrimaryScreen();

    viewportUpdateTimer_ = std::make_unique<QTimer>(this);
    viewportUpdateTimer_->setTimerType(Qt::PreciseTimer);
    viewportUpdateTimer_->setInterval(VIEWPORT_UPDATE_INTERVAL);
    viewportUpdateTimer_->start();
}

void MainWindow::centerOnPrimaryScreen()
{
    QScreen* primaryScreen = QGuiApplication::primaryScreen();
    centerOnScreen(primaryScreen);
}

void MainWindow::centerOnScreen(QScreen* screen)
{
    setScreen(screen);
    const QRect screenRect = screen->availableGeometry();
    const QRect widgetRect({}, frameSize().boundedTo(screenRect.size()));
    move(screenRect.center() - widgetRect.center());
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();
    emit applicationTerminationRequest();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    emit keyPressedEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    emit keyReleasedEvent(event);
}

void MainWindow::showEndGameDialog()
{
    EndGameDialog endGameDialog(this);

    if(endGameDialog.result() == static_cast<int>(EndGameDialog::ButtonRole::RESTART))
    {
        emit newGameRequest();
    }
    else
    {
        emit applicationTerminationRequest();
    }
}

void MainWindow::updateViewport()
{
    graphicsView_->updateViewport();
}
