#pragma once

#include "speed_level.h"
#include <QTimer>

class GameSpeedManager
{
public:
    explicit GameSpeedManager(QTimer& gameTickTimer);

    void startTimer();
    void stopTimer();

    void incrementSpeed();
    void decrementSpeed();

    void activateSpeedBoost();
    void deactivateSpeedBoost();

    void setSpeedLevel(int speedLevel);

    [[nodiscard]] int getSpeedLevelInteger() const;

private:
    void updateInterval();

    QTimer& gameTickTimer_;
    SpeedLevel speedLevel_;
};
