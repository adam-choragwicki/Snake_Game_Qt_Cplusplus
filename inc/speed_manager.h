#pragma once

#include <QSlider>
#include <QTimer>

class SpeedManager
{
public:
    explicit SpeedManager();

    const QTimer& getGameTickTimer()
    { return gameTickTimer_; }

    void start();
    void stop();

    void incrementSpeed();
    void decrementSpeed();

    void activateSpeedBoost();
    void deactivateSpeedBoost();

    void setSpeedLevel(int speedLevel);

    [[nodiscard]] int getSpeedLevel() const
    { return speedLevel_; }

private:
    QTimer gameTickTimer_;
    int speedLevel_;

    const std::map<int, int> speedLevelToDelayMsMap_{{1,  250},
                                                     {2,  230},
                                                     {3,  210},
                                                     {4,  190},
                                                     {5,  170},
                                                     {6,  150},
                                                     {7,  130},
                                                     {8,  110},
                                                     {9,  90},
                                                     {10, 70}};

    const int speedBoostDelayMs = 30;
};
