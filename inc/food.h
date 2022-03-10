#pragma once

#include <QObject>
#include <QPoint>
#include <QGraphicsEllipseItem>

class Food
{
public:
    Food() = default;

    void generate();
    [[nodiscard]] const QPoint& getPosition() const {return position_;}
    [[nodiscard]] QGraphicsEllipseItem*& getFoodGraphicalEllipseItem(){return foodSquareGraphicalEllipseItem_;}

    inline static const QColor color = Qt::red;

private:
    QPoint position_;
    QGraphicsEllipseItem* foodSquareGraphicalEllipseItem_ {};
};
