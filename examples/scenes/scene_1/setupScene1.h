#ifndef SETUP_SCENE_1_H
#define SETUP_SCENE_1_H

#include <filesystem>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>

#include "../coin/setupCoinEntity.h"
#include "../map/setupMapEntities.h"
#include "../../../SGE.hpp"


sge::Scene* setupScene1(sge::Universe* universe, sge::Entity* playerEntity, sf::View* view){
    sge::Scene* level1Scene = new sge::Scene();

    level1Scene->addEntity(view, playerEntity);


    tmx::Map* map = new tmx::Map();
    map->load(std::filesystem::current_path().string() + "/examples/scenes/assets/level_1.tmx");
    const auto& layers = map->getLayers();
    const auto& surface = layers[0]->getLayerAs<tmx::TileLayer>().getTiles();
    const auto& coin = layers[1]->getLayerAs<tmx::ObjectGroup>().getObjects();


    std::vector<sge::Entity*> surfaceEntities = setupMapEntities(universe, map, surface);
    level1Scene->addEntities(view, surfaceEntities);


    sge::Entity* coinEntity = setupCoinEntity(universe, coin);
    level1Scene->addEntity(view, coinEntity);


    return level1Scene;
}


#endif