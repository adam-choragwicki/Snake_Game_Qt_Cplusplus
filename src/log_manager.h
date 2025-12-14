#pragma once

#include <QFile>
#include <QTextStream>

class LogManager
{
public:
    enum class Mode
    {
        LogToConsoleOnly,
        LogToFileOnly,
        LogToFileAndConsole
    };

    enum class Verbosity
    {
        Debug,   // show everything
        Info,    // show INFO, WARN, CRITICAL, FATAL
        Warning, // only WARN and worse
        Error    // CRITICAL + FATAL
    };

    static void initialize(Mode loggingMode = Mode::LogToFileAndConsole, Verbosity verbosity = Verbosity::Debug);

private:
    static void messageHandler(QtMsgType type,
                               const QMessageLogContext& context,
                               const QString& msg);

    static QString modeToString(Mode mode);
    static QString verbosityToString(Verbosity verbosity);

    static inline auto loggingMode_ = Mode::LogToFileAndConsole;
    static inline auto verbosity_ = Verbosity::Debug;

    static inline std::unique_ptr<QFile> logFile_;
    static inline std::unique_ptr<QTextStream> logStream_;

    // turn this ON/OFF to include a source file / line in logs
    static constexpr bool ENABLE_CONTEXT_INFO = false;
};
