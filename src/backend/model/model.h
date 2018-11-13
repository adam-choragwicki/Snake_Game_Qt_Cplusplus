#pragma once

#include "snake.h"
#include "food.h"
#include "food_factory.h"
#include "food_manager.h"
#include "graphics_scene.h"
#include "arena.h"
#include "animation_manager.h"

class Model : public QObject
{
Q_OBJECT

public slots:
    void addSingleSnakeSegmentToScene(BodySegment& snakeSegment);

public:
    Model();
    void reset();

    [[nodiscard]] Arena& getArena() const
    { return *arena_; }

    [[nodiscard]] Snake& getSnake() const
    { return *snake_; }

    [[nodiscard]] FoodManager& getFoodManager()
    { return *foodManager_; }

    [[nodiscard]] GraphicsScene* getScene() const
    { return scene_.get(); }

private:
    void addItemsToScene();
    void addSnakeToScene();

    std::unique_ptr<GraphicsScene> scene_;
    std::unique_ptr<AnimationManager> animationManager_;

    std::unique_ptr<Arena> arena_;
    std::unique_ptr<Snake> snake_;
    std::unique_ptr<FoodManager> foodManager_;
};
