#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QPen>

class Coordinates;

class CustomGraphicsItem : public QGraphicsItem
{
public:
    explicit CustomGraphicsItem(const QRectF& rect);
    CustomGraphicsItem(int x, int y);

    [[nodiscard]] QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override = 0;

    void setPositionOnSceneAtCoordinates(Coordinates& coordinates);

    [[nodiscard]] uint getId() const
    { return id_; }

protected:
    bool drawRect_{};

    QRectF rect_;
    QPen pen_;
    QPen rectPen_;

private:
    const uint id_;
};
