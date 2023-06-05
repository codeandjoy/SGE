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


    return level2Scene;
}


#endif