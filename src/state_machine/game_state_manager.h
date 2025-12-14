#pragma once

#include "abstract_state.h"
#include "states/initialization_state.h"
#include "states/ready_to_start_state.h"
#include "states/running_state.h"
#include "states/escape_menu_state.h"
#include "states/game_ended_state.h"
#include "states/paused_for_debug_state.h"
#include <ranges>
#include <stdexcept>

class GameStateManager
{
public:
    explicit GameStateManager(IStateActions* stateActions) : states_{
        {GameStateType::Initialization, &initializationState_},
        {GameStateType::ReadyToStart, &readyToStartState_},
        {GameStateType::Running, &runningState_},
        {GameStateType::EscapeMenu, &escapeMenuState_},
        {GameStateType::GameEnded, &gameEndedState_},
        {GameStateType::PausedForDebug, &pausedForDebugState_}
    }
    {
        for (auto& state: states_ | std::views::values)
        {
            // Assign a state actions pointer to each state
            state->setStateActions(stateActions);
        }

        currentGameState_ = &initializationState_;
    }

    void setGameState(const GameStateType newType)
    {
        AbstractState* newState = getStateByType(newType);

        // validate transition in old state
        currentGameState_->transitionTo(newState);

        // exit old state
        currentGameState_->exited();

        // update pointer
        previousState_ = currentGameState_;
        currentGameState_ = newState;

        // enter a new state
        currentGameState_->entered();
    }

    [[nodiscard]] AbstractState* getCurrentGameState() const { return currentGameState_; }

    [[nodiscard]] GameStateType getCurrentGameStateType() const
    {
        return currentGameState_->type();
    }

    [[nodiscard]] std::optional<GameStateType> getPreviousGameStateType() const
    {
        if (!previousState_)
        {
            return std::nullopt;
        }

        return previousState_->type();
    }

    void restorePreviousGameState()
    {
        if (!previousState_)
        {
            throw std::runtime_error("No previous state to restore");
        }

        qDebug() << "Restoring previous state: " << previousState_->type();

        setGameState(previousState_->type());
        previousState_ = nullptr; // clear after use
    }

    void handleKeyPress(const int key)
    {
        currentGameState_->onKeyPress(key);
    }

private:
    AbstractState* getStateByType(GameStateType type) const
    {
        return states_.at(type);
    }

    InitializationState initializationState_;
    ReadyToStartState readyToStartState_;
    RunningState runningState_;
    EscapeMenuState escapeMenuState_;
    GameEndedState gameEndedState_;
    PausedForDebugState pausedForDebugState_;

    AbstractState* currentGameState_{};
    AbstractState* previousState_{};

    std::map<GameStateType, AbstractState*> states_;
};
