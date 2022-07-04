#pragma once

#include <QVector>

struct Coordinates
{
    friend std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates);

    Coordinates& operator+=(const Coordinates& coordinates);
    Coordinates operator+(const std::pair<int, int>& coordinates) const;
    std::pair<int, int> operator-(const Coordinates& coordinates) const;

    int x_;
    int y_;
};

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
