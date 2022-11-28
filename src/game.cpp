#include "game.h"

Game::Game()
{
    model_ = std::make_unique<Model>();
    view_ = std::make_unique<MainWindow>(model_.get());
    controller_ = std::make_unique<Controller>(model_.get(), view_.get());

    view_->show();

    controller_->subscribeToKeyEvents();
    controller_->subscribeToSpeedSliderValueChangeEvent();
    controller_->subscribeViewToGameEndEvent();
    controller_->subscribeToGameTickTimer();
    controller_->subscribeViewToSnakePositionChangedEvent();

    subscribeToRestartEvent();

    controller_->startGame();
}

void Game::subscribeToRestartEvent()
{
    connect(view_.get(), &MainWindow::restartEvent, this, &Game::processRestartEvent);
}

void Game::processRestartEvent()
{
    model_->reset();

    controller_->subscribeViewToSnakePositionChangedEvent();

    view_->getGameArena()->updateArena();

    controller_->startGame();
}
