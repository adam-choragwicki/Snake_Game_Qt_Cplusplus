#pragma once

#include <QObject>

class Controller;
class WindowManager;

class InputHandler : public QObject
{
    Q_OBJECT

public:
    explicit InputHandler(Controller* controller, WindowManager* windowManager);

    void processKeyPress(int key);

private:
    Controller* controller_{};
    WindowManager* windowManager_{};
};
