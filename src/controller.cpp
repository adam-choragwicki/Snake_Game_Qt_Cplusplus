#include "controller.h"
#include "spdlog/spdlog.h"
#include <QCoreApplication>

Controller::Controller(Model& model, MainWindow& view) : model_(model), view_(view)
{
    inputHandler_ = std::make_unique<InputHandler>(model_);
    gameLoop_ = std::make_unique<GameLoop>(model_);
    gameManager_ = std::make_unique<GameManager>(model_);

    gameManager_->setGameLoop(gameLoop_.get());

    connect(gameLoop_.get(), &GameLoop::endGame, gameManager_.get(), &GameManager::endGame);
    connect(gameLoop_.get(), &GameLoop::endGame, &view_, &MainWindow::showEndGameDialog);

    connect(&view_, &MainWindow::applicationTerminationRequest, this, &Controller::processApplicationTerminationRequest);

    subscribeToFrontendEvents();
    initializeFrontendEvents();

    gameManager_->prepareGameToStart();

    view_.getViewportUpdateTimer()->start();

    gameManager_->startGame();
}

void Controller::initializeFrontendEvents()
{
    connect(view_.getViewportUpdateTimer(), &QTimer::timeout, this, &Controller::viewportUpdateHandler);
}

void Controller::subscribeToFrontendEvents()
{
    connect(&view_, &MainWindow::keyPressedEvent, inputHandler_.get(), &InputHandler::processKeyPressedEvent);
    connect(&view_, &MainWindow::newGameRequest, gameManager_.get(), &GameManager::processRestartGameRequest);
}

void Controller::processApplicationTerminationRequest()
{
    QCoreApplication::exit(0);
}

void Controller::viewportUpdateHandler()
{
    view_.updateViewport();
}
