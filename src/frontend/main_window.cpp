#include "main_window.h"
#include "ui_main_window.h"
#include "end_game_dialog.h"
#include "config.h"

MainWindow::MainWindow(const Model& model) : QMainWindow(), ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    setWindowTitle("Snake");
    setFocus(Qt::ActiveWindowFocusReason);

    gameArena_ = std::make_unique<GameArena>(this->centralWidget(), model);
    gameArena_->setFixedSize(1560, 670);

    setFixedSize(size());

    centerOnScreen();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::centerOnScreen()
{
    const QRect screenRect = QWidget::screen()->availableGeometry();
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

QSlider* MainWindow::getSpeedSlider() const
{
    return ui_->speed_Slider;
}
