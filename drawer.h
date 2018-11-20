#ifndef DRAWER_H
#define DRAWER_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVector>
#include <QPoint>

class Drawer
{
public:
    Drawer(QGraphicsScene *mainScene);
    void drawSnake(QVector<QPoint> positions);
    void eraseSnake();

private:
    QGraphicsScene *scene;
    QVector<QGraphicsRectItem*> drawnItems;

    int square_size = 29;
};

#endif // DRAWER_H
