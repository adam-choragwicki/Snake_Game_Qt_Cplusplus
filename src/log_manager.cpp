#include "log_manager.h"

#include <ctime>
#include <iomanip>

std::ofstream logFile;
[[maybe_unused]] LogManager logManager;

LogManager::LogManager()
{
    if(appendMode_)
    {
        logFile.open(logFileName_, std::ios_base::app);
    }
    else
    {
        logFile.open(logFileName_, std::ios_base::out);
    }

    if(logFile.is_open())
    {
        std::time_t currentTime = std::time(nullptr);
        struct tm* localTime = localtime(&currentTime);
        const char* formatString = "%d-%m-%Y %H:%M";
        logFile << "<<<<<<<<<<<<<<<<<<<<" << std::put_time(localTime, formatString) << ">>>>>>>>>>>>>>>>>>>>" << std::endl;
    }
    else
    {
        throw std::runtime_error("Cannot open log file");
    }
}

LogManager::~LogManager()
{
    logFile.close();
}
