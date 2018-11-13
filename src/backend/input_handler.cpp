#include <QKeyEvent>
#include "input_handler.h"
#include "model/model.h"

InputHandler::InputHandler(Model& model) : model_(model)
{}

void InputHandler::processKeyPressedEvent(QKeyEvent* keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Left:
        case Qt::Key_A:
            model_.getSnake().setNextHeadDirection(Direction::LEFT);
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            model_.getSnake().setNextHeadDirection(Direction::RIGHT);
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            model_.getSnake().setNextHeadDirection(Direction::UP);
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            model_.getSnake().setNextHeadDirection(Direction::DOWN);
            break;
    }
}
