#pragma once

#include "model/model.h"
#include "frontend/main_window.h"
#include "model/game_speed_manager.h"

class Controller : public QObject
{
Q_OBJECT

public slots:
    void processKeyPressedEvent(QKeyEvent* keyEvent);
    void processKeyReleasedEvent(QKeyEvent* keyEvent);
    void processSliderValueChanged(int sliderValue);
    void gameTickHandler();

private slots:
    void processApplicationTerminationRequest();

public:
    Controller(Model& model, MainWindow& view);
    void startGame();

private:
    void incrementGameSpeed();
    void decrementGameSpeed();
    void endGame();

    Model& model_;
    MainWindow& view_;
};
