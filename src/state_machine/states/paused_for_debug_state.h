#pragma once

#include "../abstract_state.h"

class PausedForDebugState : public AbstractState
{
public:
    PausedForDebugState() : AbstractState("PausedForDebugState", GameStateType::PausedForDebug)
    {}

    void entered() override
    {
        stateActions_->stopGameLoop();
    }

    void transitionTo(AbstractState* newState) override
    {
        switch (newState->type())
        {
            case GameStateType::Running:
                stateActions_->startGameLoop();
                break;

            case GameStateType::EscapeMenu:
                break;

            default:
                handleIllegalTransition(newState);
        }

        printTransition(newState);
    }

    void onKeyPress(const int key) override
    {
        switch (key)
        {
            case Qt::Key_P:
                stateActions_->setGameState(GameStateType::Running);
                break;

            case Qt::Key_Escape:
                stateActions_->setGameState(GameStateType::EscapeMenu);
                break;

            default:
                break;
        }
    }
};
