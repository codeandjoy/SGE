#include <stdio.h>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "../../SGE.hpp"

int main(){
    const float GRAVITY = .3;

    printf(".▄▄ ·  ▄▄ • ▄▄▄ .\n▐█ ▀. ▐█ ▀ ▪▀▄.▀·\n▄▀▀▀█▄▄█ ▀█▄▐▀▀▪▄\n▐█▄▪▐█▐█▄▪▐█▐█▄▄▌\n ▀▀▀▀ ·▀▀▀▀  ▀▀▀ \n");



    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    window->setKeyRepeatEnabled(false); // For proper keyboard events handling (e.g. jumping)

    sge::Universe* universe = new sge::Universe(window);
    universe->setupDebug();

    sge::ScriptedView *cameraView = new sge::ScriptedView();
    cameraView->setCenter(sf::Vector2f(100, 100));
    cameraView->setSize(sf::Vector2f(250, 150));
    universe->scriptedViewManager->registerComponent(cameraView);



    // Load all textures
    universe->assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/dev/assets/pico_8_knight_sprite.png", "knight", sge::TextureSheetSizes{8, 8, 12, 12});
    universe->assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/dev/assets/pico_8_tiles.png", "picoTiles", sge::TextureSheetSizes{8, 8, 12, 12});
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
                    universe->assetsManager->getTextureSheet("picoTiles")->getTexture(),
                    universe->assetsManager->getTextureSheet("picoTiles")->getTextureRect(tiles[map.getTileCount().x*i+j].ID-1),
                    sf::Vector2f(j*map.getTileSize().x, i*map.getTileSize().y)
                ));
            }
        }
    }

    // Setup collision groups
    for(sge::Entity* entity : mapTileEntities){
        entity->collisionShapes["globalBounds"]->collisionGroups.push_back("tiles");
        entity->collisionShapes["globalBounds"]->collisionGroups.push_back("tiles+box");
        entity->collisionShapes["globalBounds"]->collisionGroups.push_back("tiles+player");
    }

    for(sge::Entity* entity : mapTileEntities){
        universe->entityManager->registerComponent(cameraView, entity);
    }
    //



    // Object layer
    auto& box = boxes[0];

    sge::Entity* boxEntity = sge::buildMobileEntity(
        universe->assetsManager->getTextureSheet("picoTiles")->getTexture(),
        universe->assetsManager->getTextureSheet("picoTiles")->getTextureRect(box.getTileID()-1),
        sf::Vector2f(box.getPosition().x, box.getPosition().y)
    );

    boxEntity->collisionShapes["globalBounds"]->collisionGroups.push_back("box");
    boxEntity->collisionShapes["globalBounds"]->collisionGroups.push_back("tiles+box");

    boxEntity->physicalObject->acceleration.y = GRAVITY;
    
    universe->entityManager->registerComponent(cameraView, boxEntity);


    sge::DebugEntity* boxDE = new sge::DebugEntity(boxEntity);
    boxDE->customCollisionShapeBorderSettings["globalBounds"] = sge::CollisionShapeBorderSettings{sf::Color::Green};
    universe->debugManager->registerComponent(cameraView, boxDE);
    //



    // Player
    sge::Entity* playerEntity = sge::buildMobileEntity(
        universe->assetsManager->getTextureSheet("knight")->getTexture(),
        universe->assetsManager->getTextureSheet("knight")->getTextureRect(9),
        sf::Vector2f(100, 50)
    );

    playerEntity->collisionShapes["globalBounds"]->setSize(sf::Vector2f(8, 4));
    playerEntity->collisionShapes["globalBounds"]->offset = sf::Vector2f(0, 4);

    playerEntity->collisionShapes["globalBounds"]->collisionGroups.push_back("player");
    playerEntity->collisionShapes["globalBounds"]->collisionGroups.push_back("tiles+player");

    playerEntity->physicalObject->acceleration.y = GRAVITY;

    sge::Animation* playerAnimation = new sge::Animation(universe->assetsManager->getTextureSheet("knight"), playerEntity->sprite, 9);
    playerAnimation->addTextureSequence("idle", std::vector<int>{9});
    playerAnimation->addTextureSequence("runRight", std::vector<int>{33, 34, 35});
    playerAnimation->addTextureSequence("runLeft", std::vector<int>{45, 46, 47});
    playerAnimation->setCurrentTextureSequence("idle");

    playerEntity->animation = playerAnimation;
    

    universe->entityManager->registerComponent(cameraView, playerEntity);


    sge::DebugEntity* playerDE = new sge::DebugEntity(playerEntity);
    playerDE->customCollisionShapeBorderSettings["globalBounds"] = sge::CollisionShapeBorderSettings{sf::Color::Red};
    // Extra debug function example
    // playerDE->addExtraDebugFunction([playerEntity](auto _){
    //     printf("%f, %f\n", playerEntity->getPosition().x, playerEntity->getPosition().y);
    // });

    universe->debugManager->registerComponent(cameraView, playerDE);
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
    sge::CollisionPair* playerAABB = new sge::CollisionPair{"player", "tiles+box"};
    playerAABB->algorithm = sge::boundingBox;
    playerAABB->startPhaseCollisionResponse = [](std::vector<sge::Collision> collisions){
        printf("start_phase\n");
    };
    playerAABB->continuousPhaseCollisionResponse = [](std::vector<sge::Collision> collisions){
        // printf("continuous_phase\n");
        sge::resolveAABB(collisions);
        sge::initiatorStandOnTopOfRecipient(collisions);
    };
    playerAABB->endPhaseCollisionResponse = [](std::vector<sge::Collision> collisions){
        printf("end_phase\n");
    };

    universe->collisionManager->registerCollisionPair("playerAABB", playerAABB);


    // To work properly, all AABB shapes should be checked together
    sge::CollisionPair* boxAABB = new sge::CollisionPair{"box", "tiles"};
    boxAABB->algorithm = sge::boundingBox;
    boxAABB->continuousPhaseCollisionResponse = [](std::vector<sge::Collision> collisions){
        sge::resolveAABB(collisions);
        sge::initiatorStandOnTopOfRecipient(collisions);
    };

    universe->collisionManager->registerCollisionPair("boxAABB", boxAABB);
    

    sge::CollisionPair* player_box = new sge::CollisionPair{"player", "box"};
    player_box->algorithm = sge::boundingBox;
    player_box->startPhaseCollisionResponse = [boxDE](std::vector<sge::Collision> collisions){
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
    };
    player_box->endPhaseCollisionResponse = [boxDE](std::vector<sge::Collision> collisions){
        boxDE->customCollisionShapeBorderSettings["globalBounds"] = sge::CollisionShapeBorderSettings{sf::Color::Green};
        
        for(sge::Collision collision : collisions){
            // TODO remove (minus) push force in the future
            collision.recipient->getOwnerEntity()->physicalObject->velocity.x = 0;
        }
    };

    universe->collisionManager->registerCollisionPair("player_box", player_box);
    //



    // Camera script
    sf::Vector2f scroll(0, 0);
    cameraView->script = [playerEntity, &scroll](sge::ScriptedView* thisView){
        sf::Vector2f center = playerEntity->sprite->getPosition();
        center.x += 4;
        center.y += 4;

        scroll.x = center.x - thisView->getCenter().x - scroll.x / 100;
        scroll.y = center.y - thisView->getCenter().y - scroll.y / 100;
        
        thisView->setCenter(center - scroll);
    };
    // 



    // Controllers and events
    universe->controllerManager->registerComponent([playerEntity, playerAnimation, universe](sf::Event event){
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

        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
            playerEntity->physicalObject->velocity.y = -120;
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
            universe->isPaused = !universe->isPaused;
        }
    });
    //



    universe->loop();

    return 0;
}