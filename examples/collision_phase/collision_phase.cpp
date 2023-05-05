#include <filesystem>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include "../../SGE.hpp"

namespace constants{
    const float GRAVITY = .3;
}

int main(){
    sge::Universe* universe = new sge::Universe();

    universe->assetsManager->loadTextureSheet(
        std::filesystem::current_path().string() + "/examples/collision_phase/assets/pico_8_tiles.png",
        "picoTiles",
        sge::TextureSheetSizes{8, 8, 12, 12}
    );
    universe->assetsManager->loadTextureSheet(
        std::filesystem::current_path().string() + "/examples/collision_phase/assets/pico_8_knight_sprite.png",
        "knight",
        sge::TextureSheetSizes{8, 8, 12, 12}
    );



    tmx::Map map;
    map.load(std::filesystem::current_path().string() + "/examples/collision_phase/assets/world.tmx");
    const auto& layers = map.getLayers();
    const auto& surface = layers[0]->getLayerAs<tmx::TileLayer>().getTiles();

    std::vector<sge::Entity*> surfaceEntities;

    for(int i = 0; i < map.getTileCount().y; i++){
        for(int j = 0; j < map.getTileCount().x; j++){
            if(surface[map.getTileCount().x*i+j].ID != 0){
                surfaceEntities.push_back(sge::buildStaticEntity(
                    universe->assetsManager->getTextureSheet("picoTiles")->getTexture(),
                    universe->assetsManager->getTextureSheet("picoTiles")->getTextureRect(surface[map.getTileCount().x*i+j].ID-1),
                    sf::Vector2f(j*map.getTileSize().x, i*map.getTileSize().y)
                ));
            }
        }
    }

    universe->entityManager->registerEntities(surfaceEntities);
    
    std::vector<sge::DebugEntity*> surfaceDebugEntities;
    for(sge::Entity* surfaceEntity : surfaceEntities){
        sge::DebugEntity* surfaceDebugEntity = new sge::DebugEntity(surfaceEntity);

        surfaceDebugEntities.push_back(surfaceDebugEntity);
        universe->debugManager->registerDebugEntity(surfaceDebugEntity);
    }



    sge::Entity* playerEntity = sge::buildMobileEntity(
        universe->assetsManager->getTextureSheet("knight")->getTexture(),
        universe->assetsManager->getTextureSheet("knight")->getTextureRect(9),
        sf::Vector2f(100,50)
    );

    playerEntity->physicalObject->acceleration.y = constants::GRAVITY;

    sge::Animation* playerAnimation = new sge::Animation(universe->assetsManager->getTextureSheet("knight"), playerEntity->sprite, 9);
    playerAnimation->addTextureSequence("idle", std::vector<int>{9});
    playerAnimation->addTextureSequence("runRight", std::vector<int>{33, 34, 35});
    playerAnimation->addTextureSequence("runLeft", std::vector<int>{45, 46, 47});
    playerAnimation->setCurrentTextureSequence("idle");

    playerEntity->animation = playerAnimation;

    universe->entityManager->registerEntity(playerEntity);

    sge::DebugEntity* playerDebugEntity = new sge::DebugEntity(playerEntity);
    playerDebugEntity->customCollisionShapeBorderSettings["globalBounds"] = sge::CollisionShapeBorderSettings{sf::Color::Red};

    universe->debugManager->registerDebugEntity(playerDebugEntity);



    std::vector<sge::CollisionShape*> playerCollisionGroup = {playerEntity->collisionShapes["globalBounds"]};
    std::vector<sge::CollisionShape*> surfaceCollisionGroup;
    for(sge::Entity* surfaceEntity : surfaceEntities){
        surfaceCollisionGroup.push_back(surfaceEntity->collisionShapes["globalBounds"]);
    }

    universe->collisionManager->registerCollisionGroup("player", playerCollisionGroup);
    universe->collisionManager->registerCollisionGroup("surface", surfaceCollisionGroup);

    sge::CollisionPair* player_surface = new sge::CollisionPair();
    player_surface->collisionGroups = std::make_pair("player", "surface");
    player_surface->checkCollision = sge::boundingBox;
    player_surface->startPhaseCollisionResponse = [surfaceDebugEntities](std::vector<sge::Collision> collisions){
        for(sge::Collision collision : collisions){
            for(sge::DebugEntity* surfaceDebugEntitity : surfaceDebugEntities){
                if(surfaceDebugEntitity->getRelatedEntity() == collision.recipient->getOwnerEntity()){
                    surfaceDebugEntitity->customCollisionShapeBorderSettings["globalBounds"] = sge::CollisionShapeBorderSettings{sf::Color::Red};
                }
            }
        }
    };
    player_surface->continuousPhaseCollisionResponse = [](std::vector<sge::Collision> collisions){
        sge::resolveAABB(collisions);
        sge::initiatorStandOnTopOfRecipient(collisions);
    };
    player_surface->endPhaseCollisionResponse = [surfaceDebugEntities](std::vector<sge::Collision> collisions){
        for(sge::Collision collision : collisions){
            for(sge::DebugEntity* surfaceDebugEntitity : surfaceDebugEntities){
                if(surfaceDebugEntitity->getRelatedEntity() == collision.recipient->getOwnerEntity()){
                    surfaceDebugEntitity->customCollisionShapeBorderSettings["globalBounds"] = sge::CollisionShapeBorderSettings();
                }
            }
        }
    };

    universe->collisionManager->registerCollisionPair("player_surface", player_surface);

    universe->addController([playerEntity, playerAnimation](){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            playerEntity->physicalObject->velocity.x = -70;
            playerAnimation->setCurrentTextureSequence("runLeft");
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            playerEntity->physicalObject->velocity.x = 70;
            playerAnimation->setCurrentTextureSequence("runRight");
        }
        else{
            playerEntity->physicalObject->velocity.x = 0;
            playerAnimation->setCurrentTextureSequence("idle");
        }
    });

    universe->addEventHandler([playerEntity](sf::Event event){
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
            playerEntity->physicalObject->velocity.y = -120;
        }
    }); 



    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000, 600), "CollisionPhase");
    sf::View* view = new sf::View(sf::Vector2f(100, 70), sf::Vector2f(250, 150));
    window->setView(*view);
    window->setKeyRepeatEnabled(false);
    
    universe->setupWindow(window);
    universe->loop();
    return 0;
}