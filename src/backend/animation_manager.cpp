#include "animation_manager.h"
#include <QPropertyAnimation>
#include <QEventLoop>

void AnimationManager::reset()
{
    animationGroup_.clear();
}

void AnimationManager::addAnimation(QPropertyAnimation* animation)
{
    animationGroup_.addAnimation(animation);
}

void AnimationManager::animateSegmentsToNewCoordinates()
{
    QEventLoop loop;
    connect(&animationGroup_, &QParallelAnimationGroup::finished, &loop, &QEventLoop::quit);
    animationGroup_.start();
    loop.exec();
}
