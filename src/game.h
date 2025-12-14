#pragma once

#include "model.h"
#include "controller.h"
#include "game_config.h"

class Game : public QObject
{
    Q_OBJECT

public:
    Game();

private:
    void printAppInfo();
    void exposeDataToQml() const;
    void initializeQmlEngine();

    std::unique_ptr<GameConfig> gameConfig_;

    std::unique_ptr<Controller> controller_;
    std::unique_ptr<Model> model_;
    /* QML engine has to be destroyed before the model and controller */
    std::unique_ptr<QQmlApplicationEngine> view_; /* QML engine as view */
};
