#pragma once

#include <iostream>
#include <QString>

struct Coordinates
{
    Coordinates(int x, int y);

    friend std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates);

    Coordinates& operator+=(const Coordinates& coordinates);
    Coordinates operator+(const std::pair<int, int>& coordinates) const;
    std::pair<int, int> operator-(const Coordinates& coordinates) const;

    [[nodiscard]] QString toString() const;

    int x_;
    int y_;
};

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
