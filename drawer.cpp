#include "drawer.h"

Drawer::Drawer(QGraphicsScene *mainScene)
{
    scene = mainScene;

    QPen red_pen(Qt::red);
    QBrush red_brush(Qt::red);

    QPen green_pen(Qt::green);
    QBrush green_brush(Qt::green);

    QPen blue_pen(Qt::blue);
    QBrush blue_brush(Qt::blue);
}

void Drawer::drawSnake(QVector<QPoint> positions)
{
    QPen red_pen(Qt::red);
    QBrush red_brush(Qt::red);

    QPen green_pen(Qt::green);
    QBrush green_brush(Qt::green);

    QPen blue_pen(Qt::blue);
    QBrush blue_brush(Qt::blue);

    //fill queue with drawn items
    for(auto item : positions)
    {
        drawnItems.append(scene->addRect(30 + item.x()*30, 30 + item.y()*30,square_size,square_size, red_pen, green_brush));
    }
}

void Drawer::eraseSnake()
{
    for(auto item : drawnItems)
    {
        scene->removeItem(item);
        //drawnItems.removeOne(item);

    }
    drawnItems.clear();
    drawnItems.squeeze();
}
