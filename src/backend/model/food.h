#pragma once

#include "custom_graphics_item.h"
#include "coordinates.h"

class Food : public CustomGraphicsItem
{
public:
    explicit Food(const Coordinates& coordinates);
    ~Food() override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void moveToNewCoordinates(const Coordinates& coordinates);

    [[nodiscard]] const Coordinates& getCoordinates() const
    { return coordinates_; }

private:
    inline static const QColor COLOR = {Qt::red};
    Coordinates coordinates_;
};
