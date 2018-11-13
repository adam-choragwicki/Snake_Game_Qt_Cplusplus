#include "model.h"
#include "spdlog/spdlog.h"

Model::Model()
{
    spdlog::debug("Initializing model");

    scene_ = std::make_unique<GraphicsScene>();
    animationManager_ = std::make_unique<AnimationManager>();

    ConfigProd::Snake snakeConfig;

    snake_ = std::make_unique<Snake>(snakeConfig.STARTING_HEAD_COORDINATES, snakeConfig.STARTING_DIRECTION, snakeConfig.STARTING_TOTAL_SEGMENT_COUNT, animationManager_.get());
    foodManager_ = std::make_unique<FoodManager>(*snake_);
    foodManager_->createFood(Coordinates{5, 11});

    arena_ = std::make_unique<Arena>(ConfigProd::Arena::PLAYABLE_HORIZONTAL_SQUARES_COUNT, ConfigProd::Arena::PLAYABLE_VERTICAL_SQUARES_COUNT);

    connect(snake_.get(), &Snake::segmentAdded, this, &Model::addSingleSnakeSegmentToScene);

    addItemsToScene();
}

void Model::reset()
{
    snake_->reset();
    foodManager_->reset();
}

void Model::addItemsToScene()
{
    for(auto&[_, backgroundTile] : arena_->getBackgroundTiles())
    {
        //qDebug() << "Adding background tiles to scene";
        scene_->addItem(backgroundTile.get());
    }

    for(auto&[_, boundary] : arena_->getBoundaries())
    {
        //qDebug() << "Adding arena boundary to scene";
        scene_->addItem(boundary.get());
    }

    addSnakeToScene();

    scene_->addItem(&foodManager_->getFood());
}

void Model::addSnakeToScene()
{
    //qDebug() << "Adding snake to scene";

    for(auto& snakeSegment : snake_->getSegments())
    {
        addSingleSnakeSegmentToScene(*snakeSegment);
    }
}

void Model::addSingleSnakeSegmentToScene(BodySegment& snakeSegment)
{
    //qDebug() << "Adding single snake segment " << snakeSegment.getId() << " to scene";
    scene_->addItem(&snakeSegment);
}
