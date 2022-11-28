#include "speed_manager.h"
#include "config.h"

SpeedManager::SpeedManager()
{
    speedLevel_ = Config::Speed::DEFAULT_SPEED_LEVEL;
}

void SpeedManager::incrementSpeed()
{
    if(speedLevel_ < Config::Speed::MAX_SPEED_LEVEL)
    {
        ++speedLevel_;
    }
}

void SpeedManager::decrementSpeed()
{
    if(speedLevel_ > Config::Speed::MIN_SPEED_LEVEL)
    {
        --speedLevel_;
    }
}

void SpeedManager::activateSpeedBoost()
{
    gameTickTimer_.setInterval(speedBoostDelayMs);
}

void SpeedManager::deactivateSpeedBoost()
{
    setSpeedLevel(speedLevel_);
}

void SpeedManager::setSpeedLevel(int speedLevel)
{
    gameTickTimer_.setInterval(speedLevelToDelayMsMap_.at(speedLevel));
}

void SpeedManager::start()
{
    gameTickTimer_.start();
}

void SpeedManager::stop()
{
    gameTickTimer_.stop();
}
