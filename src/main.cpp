#include "game.h"
#include "log_manager.h"

int main(int argc, char* argv[])
{
    try
    {
#if defined(QT_DEBUG)
        LogManager::initialize(LogManager::Mode::LogToFileAndConsole, LogManager::Verbosity::Debug);
#else
        LogManager::initialize(LogManager::Mode::LogToFileOnly, LogManager::Verbosity::Info);
#endif

        QGuiApplication app(argc, argv);

        Game game;

        return QGuiApplication::exec();
    }
    catch (const std::exception& e)
    {
        qCritical() << "Unhandled exception:" << e.what();
        return 1;
    }
    catch (...)
    {
        qCritical() << "Unhandled unknown exception";
        return 1;
    }
}

// TODO FEATURE add sounds
// TODO OPTIONAL FEATURE add keyboard support to escape overlay end game overlay
// TODO OPTIONAL FEATURE make snake rotate fluently
