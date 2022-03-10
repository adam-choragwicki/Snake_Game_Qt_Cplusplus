#pragma once

#include <QSlider>
#include <QTimer>

class SpeedManager
{
public:
    explicit SpeedManager() = default;

    void connectSlider(QSlider& slider);
    void processIncreaseSpeed();
    void processDecreaseSpeed();

    void activateSpeedBoost();
    void deactivateSpeedBoost();
    void setGameSpeedLevel();
    void stopGame();
    void resetSpeed();
    QTimer& getGameTickTimer();

private:
    QSlider* slider_ = nullptr;
    QTimer gameTickTimer_;
    const int defaultSpeedLevel = 5;
};
