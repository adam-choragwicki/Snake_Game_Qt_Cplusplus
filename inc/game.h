#pragma once

#include "model.h"
#include "view/main_window.h"
#include "controller.h"

#include <memory>

class Game : public QObject
{
Q_OBJECT

public slots:
    void processRestartEvent();

public:
    Game();

private:
    void subscribeToRestartEvent();

    std::unique_ptr<Model> model_;
    std::unique_ptr<MainWindow> view_;
    std::unique_ptr<Controller> controller_;
};
