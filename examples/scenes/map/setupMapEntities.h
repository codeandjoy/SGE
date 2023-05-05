#ifndef SETUP_MAP_ENTITIES
#define SETUP_MAP_ENTITIES

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include "../../../SGE.hpp"


std::vector<sge::Entity*> setupMapEntities(sge::Universe* universe, auto map, auto surface){
    std::vector<sge::Entity*> surfaceEntities;
    for(int i = 0; i < map->getTileCount().y; i++){
        for(int j = 0; j < map->getTileCount().x; j++){
            if(surface[map->getTileCount().x*i+j].ID != 0){
                surfaceEntities.push_back(sge::buildStaticEntity(
                    universe->assetsManager->getTextureSheet("picoTiles")->getTexture(),
                    universe->assetsManager->getTextureSheet("picoTiles")->getTextureRect(surface[map->getTileCount().x*i+j].ID-1),
                    sf::Vector2f(j*map->getTileSize().x, i*map->getTileSize().y)
                ));
            }
        }
    }
    
    return surfaceEntities;
}


#endif