#ifndef SETUP_SCENE_2_H
#define SETUP_SCENE_2_H

#include <filesystem>
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include "tmxlite/ObjectGroup.hpp"

#include "../heart/setupHeartEntity.h"
#include "../map/setupMapEntities.h"
#include "../../../SGE.hpp"


sge::Scene* setupScene2(sge::Universe* universe, sge::Entity* playerEntity){
    sge::Scene* level2Scene = new sge::Scene();


    level2Scene->registerEntity(playerEntity);



    tmx::Map* map = new tmx::Map();
    map->load(std::filesystem::current_path().string() + "/examples/scenes/assets/level_2.tmx");
    const auto& layers = map->getLayers();
    const auto& surface = layers[0]->getLayerAs<tmx::TileLayer>().getTiles();
    const auto& heart = layers[1]->getLayerAs<tmx::ObjectGroup>().getObjects();



    std::vector<sge::Entity*> surfaceEntities = setupMapEntities(universe, map, surface);
    level2Scene->registerEntities(surfaceEntities);



    sge::Entity* heartEntity = setupHeartEntity(universe, heart);
    level2Scene->registerEntity(heartEntity);



    std::vector<sge::CollisionShape*> surfaceCollisionGroup;
    for(sge::Entity* surfaceEntity : surfaceEntities){
        surfaceCollisionGroup.push_back(surfaceEntity->collisionShapes["globalBounds"]);
    }
    std::vector<sge::CollisionShape*> playerCollisionGroup = {playerEntity->collisionShapes["globalBounds"]};
    std::vector<sge::CollisionShape*> heartCollisionGroup = {heartEntity->collisionShapes["globalBounds"]};

    level2Scene->registerCollisionGroup("surface", surfaceCollisionGroup);
    level2Scene->registerCollisionGroup("player", playerCollisionGroup);
    level2Scene->registerCollisionGroup("heart", heartCollisionGroup);



    sge::CollisionPair* player_surface = new sge::CollisionPair();
    player_surface->collisionGroups = std::make_pair("player", "surface");
    player_surface->checkCollision = sge::boundingBox;
    player_surface->continuousPhaseCollisionResponse = [](std::vector<sge::Collision> collisions){
        sge::resolveAABB(collisions);
        sge::initiatorStandOnTopOfRecipient(collisions);
    };

    level2Scene->registerCollisionPair("player_surface", player_surface);

    sge::CollisionPair* player_heart = new sge::CollisionPair();
    player_heart->collisionGroups = std::make_pair("player", "heart");
    player_heart->checkCollision = sge::boundingBox;
    player_heart->startPhaseCollisionResponse = [universe, playerEntity](auto _){
        playerEntity->physicalObject->setPosition(sf::Vector2f(100, 50));
        universe->sceneManager->setCurrentScene("level_1");
    };

    level2Scene->registerCollisionPair("player_heart", player_heart);



    return level2Scene;
}


#endif