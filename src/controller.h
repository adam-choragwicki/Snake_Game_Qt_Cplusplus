#pragma once

#include "model.h"
#include "input_handler.h"
#include "game_loop.h"
#include "game_coordinator.h"
#include "window_manager.h"
#include "qml_helper.h"
#include "state_machine/game_state_manager.h"
#include "state_machine/game_state_type.h"
#include "state_machine/i_state_actions.h"
#include "overlay_manager.h"
#include <QQmlApplicationEngine>

class Controller : public QObject, public IStateActions
{
    Q_OBJECT

signals:
    void applicationShutdownRequested();

public slots:
    void onQmlEngineFullyInitialized();
    void processKeyPress(int key);
    void onResumeClicked();
    void onRestartClicked();
    void onQuitClicked();
    void onPlayAgainClicked();

public:
    Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view);

    // IStateActions implementation
    void startGameLoop() override;
    void stopGameLoop() override;

    void processSnakeDirectionKeyPress(const Direction& nextDirection) override;

    void enableSnakeAnimation() override;
    void disableSnakeAnimation() override;

    void spawnFoodAtCoordinates(const Coordinates& coordinates) override;

    void showStartingImageOverlay() override;
    void hideStartingImageOverlay() override;

    void showEndGameOverlay() override;
    void hideEndGameOverlay() override;

    void showEscapeMenuOverlay() override;
    void hideEscapeMenuOverlay() override;

    void setGameState(GameStateType newGameState) override;
    void restorePreviousState() override;

    [[nodiscard]] GameStateManager& getStateManager() { return gameStateManager_; }

    [[nodiscard]] QSize getInitialRenderResolution() const { return windowManager_.getInitialRenderResolution(); }
    Q_PROPERTY(QSize initialRenderResolution READ getInitialRenderResolution CONSTANT)

    [[nodiscard]] bool isStartInFullScreenEnabled() const { return windowManager_.isStartInFullScreenEnabled(); }
    Q_PROPERTY(bool startInFullScreenEnabled READ isStartInFullScreenEnabled CONSTANT)

private slots:
    void gameEnded();

private:
    const GameConfig& gameConfig_;
    Model& model_;
    QQmlApplicationEngine& view_;
    std::unique_ptr<GameLoop> gameLoop_;

    QmlHelper qmlHelper_{view_};
    GameStateManager gameStateManager_;
    WindowManager windowManager_;
    std::unique_ptr<OverlayManager> overlayManager_;
    std::unique_ptr<InputHandler> inputHandler_;
    std::unique_ptr<GameCoordinator> gameCoordinator_;
};
