#pragma once

#include "common.h"

#include <QMessageBox>
#include <QPushButton>

class EndGameDialog : public QMessageBox
{
public:
    EndGameDialog(QWidget* parent, GameResult gameResult);
    ~EndGameDialog() override = default;

    enum class ButtonRole
    {
        RESTART = 0, EXIT = 1
    };
};
