#pragma once

#include <QString>

class ScoreManager
{
public:
    void reset() { score_ = 0; }

    void increaseScore() { ++score_; }

    [[nodiscard]] QString getScoreAsString() const { return QString::number(score_); }

private:
    int score_{0};
};
