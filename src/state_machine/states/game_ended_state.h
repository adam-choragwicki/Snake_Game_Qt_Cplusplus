#pragma once

#include "../abstract_state.h"

class GameEndedState : public AbstractState
{
public:
    GameEndedState() : AbstractState("GameEndedState", GameStateType::GameEnded)
    {}

    void entered() override
    {
        qDebug() << "Entered state: GameEnded";
        stateActions_->showEndGameOverlay();
        stateActions_->stopGameLoop();
    }

    void exited() override
    {
        qDebug() << "Exited state: GameEnded";
        stateActions_->hideEndGameOverlay();
    }

    void transitionTo(AbstractState* newState) override
    {
        switch (newState->type())
        {
            case GameStateType::ReadyToStart:
                break;

            default:
                handleIllegalTransition(newState);
        }

        printTransition(newState);
    }
};
