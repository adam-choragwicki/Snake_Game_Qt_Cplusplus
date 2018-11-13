#include "game.h"

Game::Game()
{
    model_ = std::make_unique<Model>();
    view_ = std::make_unique<MainWindow>(*model_);
    controller_ = std::make_unique<Controller>(*model_, *view_);

    view_->show();
}
