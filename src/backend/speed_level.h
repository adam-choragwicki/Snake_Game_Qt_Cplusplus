#pragma once

class SpeedLevel
{
public:
    explicit SpeedLevel(int level);
    bool operator<(const SpeedLevel& other) const;
    [[nodiscard]] int toInt() const;

    void increment();
    void decrement();

private:
    int level_;
};
