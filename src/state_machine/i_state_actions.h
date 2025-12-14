#pragma once

#include "game_state_type.h"

class IStateActions
{
public:
    virtual ~IStateActions() = default;

    // Game loop control
    virtual void startGameLoop() = 0;
    virtual void stopGameLoop() = 0;

    // Snake
    virtual void processSnakeDirectionKeyPress(const Direction& nextDirection) = 0;
    virtual void enableSnakeAnimation() = 0;
    virtual void disableSnakeAnimation() = 0;

    // Food
    virtual void spawnFoodAtCoordinates(const Coordinates& coordinates) = 0;

    // Overlays
    virtual void showStartingImageOverlay() = 0;
    virtual void hideStartingImageOverlay() = 0;
    virtual void showEscapeMenuOverlay() = 0;
    virtual void hideEscapeMenuOverlay() = 0;
    virtual void showEndGameOverlay() = 0;
    virtual void hideEndGameOverlay() = 0;

    // State transitions
    virtual void setGameState(GameStateType newType) = 0;
    virtual void restorePreviousState() = 0;
};
