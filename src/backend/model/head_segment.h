#pragma once

#include "body_segment.h"

class HeadSegment : public BodySegment
{
public:
    HeadSegment(const Coordinates& coordinates, const Direction& movementDirection, AnimationManager* animationManager);
    ~HeadSegment() override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void setNewPupilSightTargetPosition(const QPointF& pupilSightTargetPosition);

private:
    void drawEyes(QPainter* painter, int eyeXOffset, int eyeYOffset);
    void drawPupils(QPainter* painter, int eye1X, int eye1Y, int eye2X, int eye2Y);
    static void drawEyeSockets(QPainter* painter, int eye1X, int eye1Y, int eye2X, int eye2Y);

    void updatePupilPosition();

    inline static const QColor COLOR = Qt::yellow;
    inline static const QColor EYE_SOCKET_COLOR = Qt::white;
    inline static const QColor PUPIL_COLOR = Qt::black;

    inline static const int EYE_SOCKETS_SPACING = 10;
    inline static const int EYE_SOCKET_SIZE = 18;
    inline static constexpr int HALF_EYE_SOCKET_SIZE = EYE_SOCKET_SIZE / 2;

    inline static const int PUPIL_SIZE = 8;
    inline static constexpr int HALF_PUPIL_SIZE = PUPIL_SIZE / 2;

    QPoint pupilOffset_;
    QPointF pupilSightTargetPosition_;
};
