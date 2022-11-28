#pragma once

#include "model.h"
#include "view/main_window.h"
#include "speed_manager.h"

class Controller : public QObject
{
Q_OBJECT

signals:
    void gameEndEvent(GameResult gameResult);

public slots:
    void processKeyPressedEvent(Key key);
    void processSpeedBoostKeyReleasedEvent();
    void processSliderValueChanged(int sliderValue);
    void gameTickHandler();

public:
    Controller(Model* model, MainWindow* view);

    void subscribeToKeyEvents();
    void subscribeToSpeedSliderValueChangeEvent();
    void subscribeViewToGameEndEvent();
    void subscribeToGameTickTimer();
    void subscribeViewToSnakePositionChangedEvent();
    void startGame();
    void endGame();

    void incrementGameSpeed();
    void decrementGameSpeed();

private:
    Model* model_{};
    MainWindow* view_{};

    SpeedManager speedManager_;
};
