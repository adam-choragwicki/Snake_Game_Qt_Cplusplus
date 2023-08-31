#pragma once

#include <QMessageBox>
#include <QPushButton>

class EndGameDialog : public QMessageBox
{
public:
    explicit EndGameDialog(QWidget* parent);
    ~EndGameDialog() override = default;

    enum class ButtonRole
    {
        RESTART = 0, EXIT = 1
    };
};
