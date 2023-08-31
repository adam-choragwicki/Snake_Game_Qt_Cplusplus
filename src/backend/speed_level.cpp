#include "speed_level.h"
#include "config.h"

SpeedLevel::SpeedLevel(int level)
{
    if(level >= Config::Speed::MIN_SPEED_LEVEL && level <= Config::Speed::MAX_SPEED_LEVEL)
    {
        level_ = level;
    }
    else
    {
        throw std::runtime_error("Error, wrong speed level: " + std::to_string(level));
    }
}

bool SpeedLevel::operator<(const SpeedLevel& other) const
{
    return level_ < other.level_;
}

int SpeedLevel::toInt() const
{
    return level_;
}

void SpeedLevel::increment()
{
    if(level_ < Config::Speed::MAX_SPEED_LEVEL)
    {
        ++level_;
    }
}

void SpeedLevel::decrement()
{
    if(level_ > Config::Speed::MIN_SPEED_LEVEL)
    {
        --level_;
    }
}
