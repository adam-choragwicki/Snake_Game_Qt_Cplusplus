#pragma once

#include "abstract_background_tile.h"

class BackgroundTile1 : public AbstractBackgroundTile
{
public:
    BackgroundTile1(int x, int y);

private:
    static constexpr QColor COLOR{170, 215, 81};
};

class BackgroundTile2 : public AbstractBackgroundTile
{
public:
    BackgroundTile2(int x, int y);

private:
    static constexpr QColor COLOR{162, 209, 73};
};
