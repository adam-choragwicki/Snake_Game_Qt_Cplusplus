#include "end_game_dialog.h"

#include <QApplication>

EndGameDialog::EndGameDialog(QWidget* parent) : QMessageBox(parent)
{
    setIcon(QMessageBox::Icon::Warning);
    setWindowTitle("Game over");
    setText("Oops, do you want to play again?");

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
