#pragma once

#include "../abstract_state.h"

class InitializationState : public AbstractState
{
public:
    InitializationState() : AbstractState("InitializationState", GameStateType::Initialization)
    {}

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
