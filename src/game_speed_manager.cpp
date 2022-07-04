#include "game_speed_manager.h"

SpeedManager::SpeedManager(QSlider* gameSpeedSlider)
{
    slider_ = gameSpeedSlider;
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
    const int boostValue = 20;
    gameTickTimer_.setInterval(boostValue);
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

void SpeedManager::startGame()
{
    gameTickTimer_.start();
}

void SpeedManager::stopGame()
{
    gameTickTimer_.stop();
}

QTimer& SpeedManager::getGameTickTimer()
{
    return gameTickTimer_;
}
