#pragma once

#include "model/custom_graphics_item.h"

class Wall : public CustomGraphicsItem
{
public:
    Wall(int x, int y);

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    static constexpr QColor COLOR{160, 54, 35};
};
