#ifndef SETUP_SCENE_2_H
#define SETUP_SCENE_2_H

#include <filesystem>
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include "tmxlite/ObjectGroup.hpp"

#include "../heart/setupHeartEntity.h"
#include "../map/setupMapEntities.h"
#include "../../../SGE.hpp"


sge::Scene* setupScene2(sge::Universe* universe, sge::Entity* playerEntity, sf::View* view){
    sge::Scene* level2Scene = new sge::Scene();


    level2Scene->addEntity(view, playerEntity);



    tmx::Map* map = new tmx::Map();
    map->load(std::filesystem::current_path().string() + "/examples/scenes/assets/level_2.tmx");
    const auto& layers = map->getLayers();
    const auto& surface = layers[0]->getLayerAs<tmx::TileLayer>().getTiles();
    const auto& heart = layers[1]->getLayerAs<tmx::ObjectGroup>().getObjects();



    std::vector<sge::Entity*> surfaceEntities = setupMapEntities(universe, map, surface);
    level2Scene->addEntities(view, surfaceEntities);



    sge::Entity* heartEntity = setupHeartEntity(universe, heart);
    level2Scene->addEntity(view, heartEntity);



    std::vector<sge::CollisionShape*> surfaceCollisionGroup;
    for(sge::Entity* surfaceEntity : surfaceEntities){
        surfaceCollisionGroup.push_back(surfaceEntity->collisionShapes["globalBounds"]);
    }
    std::vector<sge::CollisionShape*> playerCollisionGroup = {playerEntity->collisionShapes["globalBounds"]};
    std::vector<sge::CollisionShape*> heartCollisionGroup = {heartEntity->collisionShapes["globalBounds"]};

    level2Scene->addCollisionGroup("surface", surfaceCollisionGroup);
    level2Scene->addCollisionGroup("player", playerCollisionGroup);
    level2Scene->addCollisionGroup("heart", heartCollisionGroup);



    sge::CollisionPair* player_surface = new sge::CollisionPair{ "player", "surface" };
    player_surface->algorithm = sge::boundingBox;
    player_surface->continuousPhaseCollisionResponse = [](std::vector<sge::Collision> collisions){
        sge::resolveAABB(collisions);
        sge::initiatorStandOnTopOfRecipient(collisions);
    };

    level2Scene->addCollisionPair("player_surface", player_surface);

    sge::CollisionPair* player_heart = new sge::CollisionPair{ "player", "heart" };
    player_heart->algorithm = sge::boundingBox;
    player_heart->startPhaseCollisionResponse = [universe, playerEntity](auto _){
        playerEntity->sprite->setPosition(sf::Vector2f(100, 50));
        universe->drumSceneManager->setCurrentScene("level_1");
    };

    level2Scene->addCollisionPair("player_heart", player_heart);



    return level2Scene;
}


#endif