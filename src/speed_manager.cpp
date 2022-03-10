#include "speed_manager.h"

void SpeedManager::connectSlider(QSlider& slider)
{
    slider_ = &slider;
}

void SpeedManager::resetSpeed()
{
    slider_->setValue(defaultSpeedLevel);
    setGameSpeedLevel();
}

void SpeedManager::processIncreaseSpeed()
{
    int sliderValue = slider_->value();

    /*Subtracting means increasing speed*/
    slider_->setValue(sliderValue - 1);
}

void SpeedManager::processDecreaseSpeed()
{
    int sliderValue = slider_->value();

    /*Adding means decreasing speed*/
    slider_->setValue(sliderValue + 1);
}

void SpeedManager::activateSpeedBoost()
{
    const int BOOST_VALUE = 20;
    gameTickTimer_.setInterval(BOOST_VALUE);
}

void SpeedManager::deactivateSpeedBoost()
{
    setGameSpeedLevel();
}

void SpeedManager::setGameSpeedLevel()
{
    const int timeOffset = 20;
    const int speedLevel = slider_->value();

    gameTickTimer_.setInterval(timeOffset + speedLevel * 20);
}

void SpeedManager::stopGame()
{
    gameTickTimer_.stop();
}

QTimer& SpeedManager::getGameTickTimer()
{
    return gameTickTimer_;
}
