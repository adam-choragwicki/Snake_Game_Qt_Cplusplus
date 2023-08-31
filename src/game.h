#pragma once

#include "model/model.h"
#include "frontend/main_window.h"
#include "controller.h"

class Game
{
public:
    Game();

private:
    std::unique_ptr<Model> model_;
    std::unique_ptr<MainWindow> view_;
    std::unique_ptr<Controller> controller_;
};
