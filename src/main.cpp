#include "game.h"
#include <QApplication>

#include "spdlog/spdlog.h"
#include <spdlog/sinks/basic_file_sink.h>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    bool enableLogging = true;

    if(enableLogging)
    {
        bool logToFile = true;

        spdlog::set_level(spdlog::level::debug);

        if(logToFile)
        {
            spdlog::default_logger()->sinks().push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/log.txt", true));
        }

        spdlog::flush_on(spdlog::level::debug);
    }
    else
    {
        spdlog::set_level(spdlog::level::off);
    }

    Game game;

    return QApplication::exec();
}
