#pragma once

#include <QSlider>
#include <QTimer>

class SpeedManager
{
public:
    explicit SpeedManager(QSlider* gameSpeedSlider);

    void processIncreaseSpeed();
    void processDecreaseSpeed();
    void activateSpeedBoost();
    void deactivateSpeedBoost();
    void setGameSpeedLevel();
    void startGame();
    void stopGame();
    QTimer& getGameTickTimer();

private:
    QSlider* slider_ {};
    QTimer gameTickTimer_;
    const int defaultSpeedLevel = 5;
};
