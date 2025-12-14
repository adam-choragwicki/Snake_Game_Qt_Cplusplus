#pragma once

#include "../abstract_state.h"

class EscapeMenuState : public AbstractState
{
public:
    EscapeMenuState() : AbstractState("EscapeMenuState", GameStateType::EscapeMenu)
    {}

    void entered() override
    {
        qDebug() << "Entered state: EscapeMenu";
        stateActions_->showEscapeMenuOverlay();
        stateActions_->stopGameLoop();
    }

    void exited() override
    {
        qDebug() << "Exited state: EscapeMenu";
        stateActions_->hideEscapeMenuOverlay();
    }

    void transitionTo(AbstractState* newState) override
    {
        switch (newState->type())
        {
            case GameStateType::ReadyToStart:
            case GameStateType::Running:
            case GameStateType::PausedForDebug:
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
            case Qt::Key_Escape:
                stateActions_->restorePreviousState();
                break;

            default:
                break;
        }
    }
};
