#include "controller.h"
#include <QQmlContext>

Controller::Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view) : gameConfig_(gameConfig), model_(model), view_(view), gameStateManager_(this)
{
    gameLoop_ = std::make_unique<GameLoop>(model_, gameConfig_.SNAKE_MOVEMENT_INTERVAL_MS);

    // Initialize these early so Q_PROPERTY getters work when QML loads
    gameCoordinator_ = std::make_unique<GameCoordinator>(model_, *gameLoop_);
    inputHandler_ = std::make_unique<InputHandler>(this, &windowManager_);

    connect(gameLoop_.get(), &GameLoop::endGame, this, &Controller::gameEnded);
}

void Controller::onQmlEngineFullyInitialized()
{
    qDebug() << "QML engine fully initialized";

    windowManager_.setWindow(qmlHelper_.getMainWindow());
    overlayManager_ = std::make_unique<OverlayManager>(qmlHelper_);

    // Now that QML is loaded, provide QmlHelper to GameCoordinator
    gameCoordinator_->setQmlHelper(&qmlHelper_);

    qInfo() << "Game started. Resolution =" << windowManager_.getInitialRenderResolution().width() << "x" << windowManager_.getInitialRenderResolution().height();
    setGameState(GameStateType::ReadyToStart);
}

void Controller::startGameLoop()
{
    // qDebug() << "Controller::startGameLoop()";
    gameCoordinator_->startGameLoop();
}

void Controller::stopGameLoop()
{
    // qDebug() << "Controller::stopGameLoop()";
    gameCoordinator_->stopGameLoop();
}

void Controller::showStartingImageOverlay()
{
    overlayManager_->showStartingImageOverlay();
}

void Controller::hideStartingImageOverlay()
{
    overlayManager_->hideStartingImageOverlay();
}

void Controller::showEndGameOverlay()
{
    overlayManager_->showEndGameOverlay(model_.getScoreManager().getScoreAsString());
}

void Controller::hideEndGameOverlay()
{
    overlayManager_->hideEndGameOverlay();
}

void Controller::showEscapeMenuOverlay()
{
    overlayManager_->showEscapeMenuOverlay();
}

void Controller::hideEscapeMenuOverlay()
{
    overlayManager_->hideEscapeMenuOverlay();
}

void Controller::setGameState(const GameStateType newGameState)
{
    gameStateManager_.setGameState(newGameState);
}

void Controller::restorePreviousState()
{
    gameStateManager_.restorePreviousGameState();
}

void Controller::processKeyPress(const int key)
{
    // qDebug() << "Key pressed:" << key;
    inputHandler_->processKeyPress(key);
}

void Controller::onResumeClicked()
{
    qInfo() << "Resume button clicked";
    gameStateManager_.restorePreviousGameState();
}

void Controller::onRestartClicked()
{
    qInfo() << "Restart button clicked";
    gameCoordinator_->restartGame();
    gameStateManager_.setGameState(GameStateType::ReadyToStart);
}

void Controller::onQuitClicked()
{
    qInfo() << "Quit button clicked";
    emit applicationShutdownRequested();
}

void Controller::onPlayAgainClicked()
{
    qInfo() << "Play again button clicked";
    gameCoordinator_->restartGame();
    gameStateManager_.setGameState(GameStateType::ReadyToStart);
}

void Controller::gameEnded()
{
    qInfo() << "Game ended";
    setGameState(GameStateType::GameEnded);
}

void Controller::processSnakeDirectionKeyPress(const Direction& nextDirection)
{
    // qDebug() << "processSnakeDirectionKeyPress:" << static_cast<int>(nextDirection);
    model_.getSnake().setNextHeadDirection(nextDirection);
}

void Controller::enableSnakeAnimation()
{
    qmlHelper_.getSnakeLayer()->setProperty("snakeAnimationsEnabled", true);
}

void Controller::disableSnakeAnimation()
{
    qmlHelper_.getSnakeLayer()->setProperty("snakeAnimationsEnabled", false);
}

void Controller::spawnFoodAtCoordinates(const Coordinates& coordinates)
{
    model_.getFoodManager().spawnFoodAtCoordinates(coordinates);
}
