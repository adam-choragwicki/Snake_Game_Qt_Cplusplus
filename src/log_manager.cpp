#include "log_manager.h"
#include <QDir>

void LogManager::initialize(const Mode loggingMode, const Verbosity verbosity)
{
    loggingMode_ = loggingMode;
    verbosity_ = verbosity;

    if (loggingMode_ == Mode::LogToFileOnly || loggingMode_ == Mode::LogToFileAndConsole)
    {
        // Try to create a "logs/" directory
        if (!QDir().mkpath("logs"))
        {
            fprintf(stderr, "[LogManager] Failed to create logs directory! File logging disabled.\n");
            loggingMode_ = Mode::LogToConsoleOnly;
        }
        else
        {
            // Create a fresh log file for each run
            const QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
            QString logFileName = QString("logs/%1.log").arg(timestamp);

            // Try to open a log file
            logFile_ = std::make_unique<QFile>(logFileName);

            if (!logFile_->open(QIODevice::WriteOnly | QIODevice::Text))
            {
                fprintf(stderr, "[LogManager] Failed to open log file %s! File logging disabled.\n", logFileName.toUtf8().constData());
                logFile_.reset();
                loggingMode_ = Mode::LogToConsoleOnly;
            }
            else
            {
                logStream_ = std::make_unique<QTextStream>(logFile_.get());
            }
        }
    }

    qInstallMessageHandler(messageHandler);

    qDebug() << "Logging initialized, mode =" << modeToString(loggingMode_) << ", verbosity =" << verbosityToString(verbosity_);
}

void LogManager::messageHandler(const QtMsgType type,
                                const QMessageLogContext& context,
                                const QString& msg)
{
    // verbosity filtering
    bool shouldLog = false;

    switch (type)
    {
        case QtDebugMsg:
            shouldLog = verbosity_ == Verbosity::Debug;
            break;
        case QtInfoMsg:
            shouldLog = verbosity_ == Verbosity::Debug || verbosity_ == Verbosity::Info;
            break;
        case QtWarningMsg:
            shouldLog = verbosity_ == Verbosity::Debug || verbosity_ == Verbosity::Info || verbosity_ == Verbosity::Warning;
            break;
        case QtCriticalMsg:
        case QtFatalMsg:
            shouldLog = true;
            break;
    }

    if (!shouldLog)
    {
        return;
    }

    // -------- FORMAT + OUTPUT --------
    QString level;

    switch (type)
    {
        case QtDebugMsg:    level = "DEBUG"; break;
        case QtInfoMsg:     level = "INFO"; break;
        case QtWarningMsg:  level = "WARN"; break;
        case QtCriticalMsg: level = "CRITICAL"; break;
        case QtFatalMsg:    level = "FATAL"; break;
    }

    const QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

    QString contextStr;

    if constexpr (ENABLE_CONTEXT_INFO)
    {
        contextStr = QString(" (%1:%2)")
                .arg(context.file ? context.file : "?")
                .arg(context.line);
    }

    const QString formatted = QString("[%1] [%2] %3 %4")
            .arg(timestamp)
            .arg(level)
            .arg(msg)
            .arg(contextStr);

    // Console output
    if (loggingMode_ == Mode::LogToConsoleOnly || loggingMode_ == Mode::LogToFileAndConsole)
    {
        fprintf(stderr, "%s\n", formatted.toUtf8().constData());
        fflush(stderr);
    }

    // File output
    if (logStream_)
    {
        *logStream_ << formatted << "\n";
        logStream_->flush();
    }

    if (type == QtFatalMsg)
    {
        abort();
    }
}

QString LogManager::modeToString(const Mode mode)
{
    switch (mode)
    {
        case Mode::LogToConsoleOnly: return "LogToConsoleOnly";
        case Mode::LogToFileOnly: return "LogToFileOnly";
        case Mode::LogToFileAndConsole: return "LogToFileAndConsole";
    }

    return "Unknown";
}

QString LogManager::verbosityToString(const Verbosity verbosity)
{
    switch (verbosity)
    {
        case Verbosity::Debug: return "Debug";
        case Verbosity::Info: return "Info";
        case Verbosity::Warning: return "Warning";
        case Verbosity::Error: return "Error";
    }

    return "Unknown";
}
