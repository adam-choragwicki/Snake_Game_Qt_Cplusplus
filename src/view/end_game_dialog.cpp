#include "view/end_game_dialog.h"

#include <QApplication>

EndGameDialog::EndGameDialog(QWidget* parent, GameResult gameResult) : QMessageBox(parent)
{
    if(gameResult == GameResult::WIN)
    {
        setIcon(QMessageBox::Icon::Information);
        setWindowTitle("Congratulations");
        setText("You win");
    }
    else if(gameResult == GameResult::LOSE)
    {
        setIcon(QMessageBox::Icon::Warning);
        setWindowTitle("Game over");
        setText("Oops, do you want to play again?");
    }

    setStyleSheet("color: black");

    addButton("Restart", QMessageBox::NoRole);
    addButton("Close", QMessageBox::NoRole);

    int userInput = this->exec();

    if(userInput == static_cast<int>(ButtonRole::RESTART))
    {
        setResult(static_cast<int>(ButtonRole::RESTART));
    }
    else if(userInput == static_cast<int>(ButtonRole::EXIT))
    {
        setResult(static_cast<int>(ButtonRole::EXIT));
    }
}
