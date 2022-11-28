#pragma once

#pragma once

#include <iostream>
#include <fstream>

enum LogType
{
    DEBUG, INFO, WARN, ERROR
};

class LOG
{
public:
    LOG(LogType logType) : logType_(logType)
    {
        if(!logFile_.is_open() && LOG_TO_FILE)
        {
            openFile();
        }

        operator<<("[" + getTypeLabel(logType_) + "] ");
    }

    ~LOG()
    {
        /*Append new line to every log line and flush*/
        if(LOG_TO_CONSOLE)
        {
            std::cout << std::endl;
        }

        if(LOG_TO_FILE)
        {
            logFile_ << std::endl;
        }
    }

    void openFile()
    {
        logFile_.open(LOGFILE_NAME, std::ios_base::out);

        if(!logFile_.is_open())
        {
            throw std::runtime_error("Cannot open log file");
        }
    }

    template <typename T>
    LOG& operator<<(const T& message)
    {
        if(LOG_TO_CONSOLE)
        {
            std::cout << message;
        }

        if(LOG_TO_FILE)
        {
            logFile_ << message;
        }

        return *this;
    }

private:
    inline std::string getTypeLabel(LogType logType)
    {
        switch(logType)
        {
            case DEBUG:
                return "DEBUG";
            case INFO:
                return "INFO";
            case WARN:
                return "WARN";
            case ERROR:
                return "ERROR";
            default:
                throw std::runtime_error("Unsupported log type");
        }
    }

    inline static std::ofstream logFile_;
    const LogType logType_;

    inline static const std::string LOGFILE_NAME{"log.txt"};
    static const bool LOG_TO_CONSOLE = false;
    static const bool LOG_TO_FILE = true;
};
