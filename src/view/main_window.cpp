#include "view/main_window.h"
#include "view/end_game_dialog.h"
#include "config.h"

MainWindow::MainWindow(Model* model) : QMainWindow(), ui_(std::make_unique<Ui::MainWindow>())
{
    ui_->setupUi(this);
    setWindowTitle("Snake");
    setFocus(Qt::ActiveWindowFocusReason);

    gameArena_ = std::make_unique<GameArena>(this->centralWidget(), model);
    gameArena_->setFixedSize(1560, 670);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Left:
        case Qt::Key_A:
            emit keyPressedEvent(Key::LEFT);
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            emit keyPressedEvent(Key::RIGHT);
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            emit keyPressedEvent(Key::UP);
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            emit keyPressedEvent(Key::DOWN);
            break;

        case Qt::Key_Plus:
            emit keyPressedEvent(Key::PLUS);
            break;

        case Qt::Key_Minus:
            emit keyPressedEvent(Key::MINUS);
            break;

        case Config::Key::BOOST_KEY:
            emit keyPressedEvent(Key::SPACE);
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if(event->key() == Config::Key::BOOST_KEY)
    {
        emit speedBoostKeyReleasedEvent();
    }
}

void MainWindow::processGameEndEvent(GameResult gameResult)
{
    EndGameDialog endGameDialog(this, gameResult);

    if(endGameDialog.result() == static_cast<int>(EndGameDialog::ButtonRole::RESTART))
    {
        emit restartEvent();
    }
    else
    {
        close();
    }
}
