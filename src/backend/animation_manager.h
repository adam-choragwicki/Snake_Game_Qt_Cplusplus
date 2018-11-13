#pragma once

#include <QObject>
#include <QParallelAnimationGroup>

class QPropertyAnimation;

class AnimationManager : public QObject
{
public:
    void reset();
    void addAnimation(QPropertyAnimation* animation);
    void animateSegmentsToNewCoordinates();

private:
    QParallelAnimationGroup animationGroup_;
};
