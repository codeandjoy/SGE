#include <filesystem>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include "../../SGE.hpp"


int main(){
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000, 600), "CollisionPhase");
    window->setKeyRepeatEnabled(false);
    sf::View* view = new sf::View(sf::Vector2f(100, 70), sf::Vector2f(250, 150));

    sge::Universe* universe = new sge::Universe(window);
    universe->setupDebug();
    sge::AssetsManager* assetsManager = universe->assetsManager;
    sge::EntityManager* entityManager = universe->entityManager;
    sge::DebugManager* debugManager = universe->debugManager;
    sge::CollisionManager* collisionManager = universe->collisionManager;
    sge::ControllerManager* controllerManager = universe->controllerManager;



    assetsManager->loadTextureSheet(
        std::filesystem::current_path().string() + "/examples/collision_phase/assets/pico_8_tiles.png",
        "picoTiles",
        sge::TextureSheetSizes{8, 8, 12, 12}
    );
    assetsManager->loadTextureSheet(
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
                    assetsManager->getTextureSheet("picoTiles")->getTexture(),
                    assetsManager->getTextureSheet("picoTiles")->getTextureRect(surface[map.getTileCount().x*i+j].ID-1),
                    sf::Vector2f(j*map.getTileSize().x, i*map.getTileSize().y),
                    {"surface"}
                ));
            }
        }
    }

    for(sge::Entity* entity : surfaceEntities) entityManager->registerComponent(view, entity);
    
    std::vector<sge::DebugEntity*> surfaceDebugEntities;
    for(sge::Entity* surfaceEntity : surfaceEntities){
        sge::DebugEntity* surfaceDebugEntity = new sge::DebugEntity(surfaceEntity);

        surfaceDebugEntities.push_back(surfaceDebugEntity);
        debugManager->registerComponent(view, surfaceDebugEntity);
    }



    sge::Entity* playerEntity = sge::buildMobileEntity(
        assetsManager->getTextureSheet("knight")->getTexture(),
        assetsManager->getTextureSheet("knight")->getTextureRect(9),
        sf::Vector2f(100,50),
        {"player"}
    );

    playerEntity->physicalObject->acceleration.y = .3;

    sge::Animation* playerAnimation = new sge::Animation(assetsManager->getTextureSheet("knight"), playerEntity->sprite, 9);
    playerAnimation->addTextureSequence("idle", std::vector<int>{9});
    playerAnimation->addTextureSequence("runRight", std::vector<int>{33, 34, 35});
    playerAnimation->addTextureSequence("runLeft", std::vector<int>{45, 46, 47});
    playerAnimation->setCurrentTextureSequence("idle");

    playerEntity->animation = playerAnimation;

    entityManager->registerComponent(view, playerEntity);

    sge::DebugEntity* playerDebugEntity = new sge::DebugEntity(playerEntity);
    playerDebugEntity->customCollisionShapeBorderSettings["globalBounds"] = sge::CollisionShapeBorderSettings{sf::Color::Red};

    debugManager->registerComponent(view, playerDebugEntity);



    sge::CollisionPair* player_surface = new sge::CollisionPair{ "player", "surface" };
    player_surface->algorithm = sge::boundingBox;
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

    collisionManager->registerCollisionPair("player_surface", player_surface);



    controllerManager->registerComponent([playerEntity](sf::Event event){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            playerEntity->physicalObject->velocity.x = -70;
            playerEntity->animation->setCurrentTextureSequence("runLeft");
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            playerEntity->physicalObject->velocity.x = 70;
            playerEntity->animation->setCurrentTextureSequence("runRight");
        }
        else{
            playerEntity->physicalObject->velocity.x = 0;
            playerEntity->animation->setCurrentTextureSequence("idle");
        }

        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
            playerEntity->physicalObject->velocity.y = -120;
        }
    }); 

    
    
    universe->loop();
    return 0;
}