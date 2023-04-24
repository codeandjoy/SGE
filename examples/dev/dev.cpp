#include <stdio.h>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "../../SGE.hpp"

int main(){
    const float GRAVITY = .3;

    printf(".▄▄ ·  ▄▄ • ▄▄▄ .\n▐█ ▀. ▐█ ▀ ▪▀▄.▀·\n▄▀▀▀█▄▄█ ▀█▄▐▀▀▪▄\n▐█▄▪▐█▐█▄▪▐█▐█▄▄▌\n ▀▀▀▀ ·▀▀▀▀  ▀▀▀ \n");



    sge::Universe* universe = new sge::Universe(true);



    // Load all textures
    universe->textureManager->loadTexture(std::filesystem::current_path().string() + "/examples/dev/assets/pico_8_knight_sprite.png", "knight", sge::TextureSheetSizes{8, 8, 12, 12});
    universe->textureManager->loadTexture(std::filesystem::current_path().string() + "/examples/dev/assets/pico_8_tiles.png", "picoTiles", sge::TextureSheetSizes{8, 8, 12, 12});
    //



    // Read map
    tmx::Map map;
    if(!map.load(std::filesystem::current_path().string() + "/examples/dev/assets/map.tmx")){
        printf("Can't load map");
        exit(1);
    }

    const auto& layers = map.getLayers();
    const auto& tiles = layers[0]->getLayerAs<tmx::TileLayer>().getTiles();
    const auto& boxes = layers[1]->getLayerAs<tmx::ObjectGroup>().getObjects();
    //



    // Tile layer
    std::vector<sge::Entity*> mapTileEntities;

    for(int i = 0; i < map.getTileCount().y; i++){
        for(int j = 0; j < map.getTileCount().x; j++){
            if(tiles[map.getTileCount().x*i+j].ID != 0){
                mapTileEntities.push_back(sge::buildStaticEntity(
                    universe->textureManager->getTexture("picoTiles")->getTextureSheet(),
                    universe->textureManager->getTexture("picoTiles")->getTextureRect(tiles[map.getTileCount().x*i+j].ID-1),
                    sf::Vector2f(j*map.getTileSize().x, i*map.getTileSize().y)
                ));
            }
        }
    }

    universe->entityManager->registerEntities(mapTileEntities);
    //



    // Object layer
    auto& box = boxes[0];

    sge::Entity* boxEntity = sge::buildMobileEntity(
        universe->textureManager->getTexture("picoTiles")->getTextureSheet(),
        universe->textureManager->getTexture("picoTiles")->getTextureRect(box.getTileID()-1),
        sf::Vector2f(box.getPosition().x, box.getPosition().y)
    );

    boxEntity->physicalObject->acceleration.y = GRAVITY;
    
    universe->entityManager->registerEntity(boxEntity);


    sge::DebugEntity* boxDE = new sge::DebugEntity(boxEntity);
    boxDE->customCollisionShapeBorderSettings["globalBounds"] = sge::CollisionShapeBorderSettings{sf::Color::Green};
    universe->debugManager->registerDebugEntity(boxDE); // ? make it registerDebugEntityGroup for consistency
    //



    // Player
    sge::Entity* playerEntity = sge::buildMobileEntity(
        universe->textureManager->getTexture("knight")->getTextureSheet(),
        universe->textureManager->getTexture("knight")->getTextureRect(9),
        sf::Vector2f(100, 50)
    );

    playerEntity->collisionShapes["globalBounds"]->setSize(sf::Vector2f(8, 4));
    playerEntity->collisionShapes["globalBounds"]->offset = sf::Vector2f(0, 4);

    playerEntity->physicalObject->acceleration.y = GRAVITY;

    sge::Animation* playerAnimation = new sge::Animation(universe->textureManager->getTexture("knight"), playerEntity->physicalObject, 9);
    playerAnimation->addTextureSequence("idle", std::vector<int>{9});
    playerAnimation->addTextureSequence("runRight", std::vector<int>{33, 34, 35});
    playerAnimation->addTextureSequence("runLeft", std::vector<int>{45, 46, 47});
    playerAnimation->setCurrentTextureSequence("idle");

    playerEntity->animation = playerAnimation;
    

    universe->entityManager->registerEntity(playerEntity);


    sge::DebugEntity* playerDE = new sge::DebugEntity(playerEntity);
    playerDE->customCollisionShapeBorderSettings["globalBounds"] = sge::CollisionShapeBorderSettings{sf::Color::Red};
    // Extra debug function example
    // playerDE->addExtraDebugFunction([playerEntity](auto _){
    //     printf("%f, %f\n", playerEntity->getPosition().x, playerEntity->getPosition().y);
    // });

    universe->debugManager->registerDebugEntity(playerDE);
    //



    // Collision groups
    // Player
    std::vector<sge::CollisionShape*> playerCollisionGroup =  {playerEntity->collisionShapes["globalBounds"]};
    
    // Map
    std::vector<sge::CollisionShape*> mapCollisionGroup;
    for(sge::Entity* mapTileEntity : mapTileEntities){
        mapCollisionGroup.push_back(mapTileEntity->collisionShapes["globalBounds"]);
    }

    // Box
    std::vector<sge::CollisionShape*> boxCollisionGroup = {boxEntity->collisionShapes["globalBounds"]};

    // Map tiles + Box for player AABB
    std::vector<sge::CollisionShape*> tilesAndBoxCollisionGroup = mapCollisionGroup;
    tilesAndBoxCollisionGroup.insert(tilesAndBoxCollisionGroup.end(), boxCollisionGroup.begin(), boxCollisionGroup.end());

    // Map tiles + Player for box AABB
    std::vector<sge::CollisionShape*> tilesAndPlayerCollisionGroup = mapCollisionGroup;
    tilesAndPlayerCollisionGroup.insert(tilesAndPlayerCollisionGroup.end(), playerCollisionGroup.begin(), playerCollisionGroup.end());

    universe->collisionManager->registerCollisionGroup("player", playerCollisionGroup);
    universe->collisionManager->registerCollisionGroup("tiles", mapCollisionGroup);
    universe->collisionManager->registerCollisionGroup("box", boxCollisionGroup);
    universe->collisionManager->registerCollisionGroup("tiles+box", tilesAndBoxCollisionGroup);
    universe->collisionManager->registerCollisionGroup("tiles+player", tilesAndPlayerCollisionGroup);
    //



    // Collision management
    // * Notes:
    // ! The collision shape CAN NOT be the initiator AND the recepient of the AABB response
    // ! To work properly, all AABB recipients with common initiator should be located in the SAME collision group

    // ? change collision pair to accept multiple groups, for convenience:
    // ? e.g.
    // ? createCollisionPair("name", vecInitiatorGroups{"g1name"}, vecRecipientGroups{"g2name", "g3name", "g4name"});
    // ? then loop through all initiator and recipient groups respectively when checking collisions
    // ?
    // ? to remove the need of creating extra collision groups like "tiles+box"

    // To work properly, all AABB shapes should be checked together
    universe->collisionManager->createCollisionPair("playerAABB", "player", "tiles+box");
    universe->collisionManager->setPairCollisionDetectionAlgorithm("playerAABB", sge::boundingBox);
    universe->collisionManager->setPairCollisionResponse("playerAABB", "start_phase", [](std::vector<sge::Collision> collisions){
        printf("start_phase\n");
    });
    universe->collisionManager->setPairCollisionResponse("playerAABB", "continuous_phase", [](std::vector<sge::Collision> collisions){
        // printf("continuous_phase\n");
        sge::resolveAABB(collisions);
        sge::initiatorStandOnTopOfRecipient(collisions);
    });
    universe->collisionManager->setPairCollisionResponse("playerAABB", "end_phase", [](std::vector<sge::Collision> collisions){
        printf("end_phase\n");
    });

    // To work properly, all AABB shapes should be checked together
    universe->collisionManager->createCollisionPair("boxAABB", "box", "tiles");
    universe->collisionManager->setPairCollisionDetectionAlgorithm("boxAABB", sge::boundingBox);
    universe->collisionManager->setPairCollisionResponse("boxAABB", "continuous_phase", [](std::vector<sge::Collision> collisions){
        sge::resolveAABB(collisions);
        sge::initiatorStandOnTopOfRecipient(collisions);
    });

    universe->collisionManager->createCollisionPair("PB", "player", "box");
    universe->collisionManager->setPairCollisionDetectionAlgorithm("PB", sge::boundingBox);
    universe->collisionManager->setPairCollisionResponse("PB", "start_phase", [boxDE](std::vector<sge::Collision> collisions){
        boxDE->customCollisionShapeBorderSettings["globalBounds"] = sge::CollisionShapeBorderSettings{sf::Color::Red};

        // Refactor as pushRecipient(float velocity);
        for(sge::Collision collision : collisions){
            if(collision.recipientImpactSide == sge::CollisionSide::right){
                collision.recipient->getOwnerEntity()->physicalObject->velocity.x = -10;
            }
            else if(collision.recipientImpactSide == sge::CollisionSide::left){
                collision.recipient->getOwnerEntity()->physicalObject->velocity.x = 10;
            }
        }
    });
    universe->collisionManager->setPairCollisionResponse("PB", "end_phase", [boxDE](std::vector<sge::Collision> collisions){
        boxDE->customCollisionShapeBorderSettings["globalBounds"] = sge::CollisionShapeBorderSettings{sf::Color::Green};
        
        for(sge::Collision collision : collisions){
            // TODO remove (minus) push force in the future
            collision.recipient->getOwnerEntity()->physicalObject->velocity.x = 0;
        }
    });
    //



    // Controllers and events
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
    //



    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    sf::View *view = new sf::View(sf::Vector2f(100, 100), sf::Vector2f(250, 150));
    
    window->setView(*view);
    window->setKeyRepeatEnabled(false); // For proper keyboard events handling (e.g. jumping)
    
    universe->setupWindow(window);
    
    universe->loop();

    return 0;
}