#pragma once

#include "model/model.h"
#include "frontend/main_window.h"
#include "input_handler.h"
#include "game_loop.h"
#include "game_manager.h"

class Controller : public QObject
{
Q_OBJECT

public slots:
    void viewportUpdateHandler();

private slots:
    void processApplicationTerminationRequest();

public:
    Controller(Model& model, MainWindow& view);

private:
    void subscribeToFrontendEvents();
    void initializeFrontendEvents();

    Model& model_;
    MainWindow& view_;

    std::unique_ptr<InputHandler> inputHandler_;
    std::unique_ptr<GameLoop> gameLoop_;
    std::unique_ptr<GameManager> gameManager_;
};
