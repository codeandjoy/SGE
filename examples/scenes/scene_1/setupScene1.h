#ifndef SETUP_SCENE_1_H
#define SETUP_SCENE_1_H

#include <filesystem>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "../coin/setupCoinEntity.h"
#include "../map/setupMapEntities.h"
#include "../../../SGE.hpp"


sge::Scene* setupScene1(sge::Universe* universe, sge::Entity* playerEntity){
    sge::Scene* level1Scene = new sge::Scene();


    level1Scene->registerEntity(playerEntity);



    tmx::Map* map = new tmx::Map();
    map->load(std::filesystem::current_path().string() + "/examples/scenes/assets/level_1.tmx");
    const auto& layers = map->getLayers();
    const auto& surface = layers[0]->getLayerAs<tmx::TileLayer>().getTiles();
    const auto& coin = layers[1]->getLayerAs<tmx::ObjectGroup>().getObjects();



    std::vector<sge::Entity*> surfaceEntities = setupMapEntities(universe, map, surface);
    level1Scene->registerEntities(surfaceEntities);



    sge::Entity* coinEntity = setupCoinEntity(universe, coin);
    level1Scene->registerEntity(coinEntity);



    std::vector<sge::CollisionShape*> surfaceCollisionGroup;
    for(sge::Entity* surfaceEntity : surfaceEntities){
        surfaceCollisionGroup.push_back(surfaceEntity->collisionShapes["globalBounds"]);
    }
    std::vector<sge::CollisionShape*> playerCollisionGroup = {playerEntity->collisionShapes["globalBounds"]};
    std::vector<sge::CollisionShape*> coinCollisionGroup = {coinEntity->collisionShapes["globalBounds"]};

    level1Scene->registerCollisionGroup("surface", surfaceCollisionGroup);
    level1Scene->registerCollisionGroup("player", playerCollisionGroup);
    level1Scene->registerCollisionGroup("coin", coinCollisionGroup);



    sge::CollisionPair* player_surface = new sge::CollisionPair();
    player_surface->collisionGroups = std::make_pair("player", "surface");
    player_surface->checkCollision = sge::boundingBox;
    player_surface->continuousPhaseCollisionResponse = [](std::vector<sge::Collision> collisions){
        sge::resolveAABB(collisions);
        sge::initiatorStandOnTopOfRecipient(collisions);
    };

    level1Scene->registerCollisionPair("player_surface", player_surface);

    sge::CollisionPair* player_coin = new sge::CollisionPair();
    player_coin->collisionGroups = std::make_pair("player", "coin");
    player_coin->checkCollision = sge::boundingBox;
    player_coin->startPhaseCollisionResponse = [universe, playerEntity](auto _){
        playerEntity->physicalObject->setPosition(sf::Vector2f(100, 50));
        universe->sceneManager->setCurrentScene("level_2");
    };

    level1Scene->registerCollisionPair("player_coin", player_coin);



    return level1Scene;
}


#endif