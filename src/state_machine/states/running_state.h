#pragma once

#include "../abstract_state.h"

class RunningState : public AbstractState
{
public:
    RunningState() : AbstractState("RunningState", GameStateType::Running)
    {}

    void entered() override
    {
        stateActions_->enableSnakeAnimation();
        stateActions_->startGameLoop();
    }

    void exited() override
    {
        stateActions_->disableSnakeAnimation();
    }

    void transitionTo(AbstractState* newState) override
    {
        switch (newState->type())
        {
            case GameStateType::EscapeMenu:
            case GameStateType::PausedForDebug:
            case GameStateType::GameEnded:
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
            case Qt::Key_Left:
            case Qt::Key_A:
                stateActions_->processSnakeDirectionKeyPress(Direction::LEFT);
                break;

            case Qt::Key_Right:
            case Qt::Key_D:
                stateActions_->processSnakeDirectionKeyPress(Direction::RIGHT);
                break;

            case Qt::Key_Up:
            case Qt::Key_W:
                stateActions_->processSnakeDirectionKeyPress(Direction::UP);
                break;

            case Qt::Key_Down:
            case Qt::Key_S:
                stateActions_->processSnakeDirectionKeyPress(Direction::DOWN);
                break;

            case Qt::Key_P:
                stateActions_->setGameState(GameStateType::PausedForDebug);
                break;

            case Qt::Key_Escape:
                stateActions_->setGameState(GameStateType::EscapeMenu);
                break;

            default:
                break;
        }
    }
};
