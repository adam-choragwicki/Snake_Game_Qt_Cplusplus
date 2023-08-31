#include "game_speed_manager.h"
#include "config.h"

GameSpeedManager::GameSpeedManager(QTimer& gameTickTimer) : speedLevel_(Config::Speed::DEFAULT_SPEED_LEVEL), gameTickTimer_(gameTickTimer)
{
    updateInterval();
}

void GameSpeedManager::startTimer()
{
    gameTickTimer_.start();
}

void GameSpeedManager::stopTimer()
{
    gameTickTimer_.stop();
}

void GameSpeedManager::incrementSpeed()
{
    speedLevel_.increment();
    updateInterval();
}

void GameSpeedManager::decrementSpeed()
{
    speedLevel_.decrement();
    updateInterval();
}

void GameSpeedManager::activateSpeedBoost()
{
    gameTickTimer_.setInterval(Config::Speed::SPEED_BOOST_TIMER_INTERVAL);
}

void GameSpeedManager::deactivateSpeedBoost()
{
    updateInterval();
}

void GameSpeedManager::setSpeedLevel(int speedLevel)
{
    speedLevel_ = SpeedLevel(speedLevel);
    updateInterval();
}

int GameSpeedManager::getSpeedLevelInteger() const
{
    return speedLevel_.toInt();
}

void GameSpeedManager::updateInterval()
{
    gameTickTimer_.setInterval(Config::Speed::SPEED_LEVEL_TO_TIMER_INTERVAL_MAP.at(speedLevel_));
}
