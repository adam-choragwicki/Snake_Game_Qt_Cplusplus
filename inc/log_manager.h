#pragma once

/*Including this file activates logging to LogManager::logFileName_*/
/*Please change LogManager::logFileName_ to log data to another file*/

/*By default, every program run truncates log file*/
/*In order to append to the log file please change LogManager::appendMode_ to true*/

#include <fstream>

class LogManager
{
public:
    LogManager();
    ~LogManager();
private:
    const std::string logFileName_ = "log.txt";
    const bool appendMode_ = false;
};

extern std::ofstream logFile;
