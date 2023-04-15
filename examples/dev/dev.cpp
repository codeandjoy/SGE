#include <stdio.h>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "../../SGE.hpp"

int main(){
    printf(".▄▄ ·  ▄▄ • ▄▄▄ .\n▐█ ▀. ▐█ ▀ ▪▀▄.▀·\n▄▀▀▀█▄▄█ ▀█▄▐▀▀▪▄\n▐█▄▪▐█▐█▄▪▐█▐█▄▄▌\n ▀▀▀▀ ·▀▀▀▀  ▀▀▀ \n");



    // Init
    PhysicsManager* PM = new PhysicsManager();
    CollisionManager* CM = new CollisionManager();
    TextureManager* TM = new TextureManager();
    EntityManager* EM = new EntityManager(PM, CM, TM);
    DebugManager* DM = new DebugManager();

    Universe *universe = new Universe(PM, CM, TM, EM, DM);
    //

    // Load all textures
    universe->textureManager->loadTexture(std::filesystem::current_path().string() + "/examples/dev/assets/pico_8_knight_sprite.png", "knight", TextureSheetSizes{8, 8, 12, 12});
    universe->textureManager->loadTexture(std::filesystem::current_path().string() + "/examples/dev/assets/pico_8_tiles.png", "picoTiles", TextureSheetSizes{8, 8, 12, 12});
    //



    //
    // Map
    //

    // Read
    tmx::Map map;
    if(!map.load(std::filesystem::current_path().string() + "/examples/dev/assets/map.tmx")){
        printf("Can't load map");
        exit(1);
    }

    const auto& layers = map.getLayers();
    const auto& tiles = layers[0]->getLayerAs<tmx::TileLayer>().getTiles();
    const auto& boxes = layers[1]->getLayerAs<tmx::ObjectGroup>().getObjects();
    //

    //
    // Tile layer
    //

    // Init physical objects
    std::vector<PhysicalObject*> mapTilesPOs;

    for(int i = 0; i < map.getTileCount().y; i++){
        for(int j = 0; j < map.getTileCount().x; j++){
            if(tiles[map.getTileCount().x*i+j].ID != 0){
                PhysicalObject *tile = new PhysicalObject();

                tile->setTexture(*universe->textureManager->getTexture("picoTiles")->getTextureSheet());
                tile->setTextureRect(universe->textureManager->getTexture("picoTiles")->getTextureRect(tiles[map.getTileCount().x*i+j].ID-1));
                tile->setPosition(sf::Vector2f(j*map.getTileSize().x, i*map.getTileSize().y));
                mapTilesPOs.push_back(tile);
            }
        }
    }
    // 

    // Init collision shapes
    std::vector<std::map<std::string, CollisionShape*>> mapTileCSs;
    for(PhysicalObject* tilePO : mapTilesPOs){
        mapTileCSs.push_back({{"globalBounds", new CollisionShape(tilePO)}});
    }
    //

    // Build entities
    std::vector<Entity*> mapTilesEntityGroup;
    for(int i = 0; i < mapTilesPOs.size(); i++){
        mapTilesEntityGroup.push_back(new Entity{mapTilesPOs[i], mapTileCSs[i]});
    }
    //

    // Register map tile entities
    // 1 PhysicalObject, 1 CollisionShape, no Animation
    universe->entityManager->registerEntityGroup("mapTiles", mapTilesEntityGroup);
    //

    // Register map tile debug entitites
    std::vector<DebugEntity*> mapTilesDebugEntities;
    for(Entity* tileEntity : mapTilesEntityGroup){
        DebugEntity* de = new DebugEntity(tileEntity);

        mapTilesDebugEntities.push_back(de);
        universe->debugManager->registerDebugEntity(de);
    }
    //
    
    //
    //
    //

    //
    // Object layer
    //

    auto& box = boxes[0];

    PhysicalObject* boxPO = new PhysicalObject();
    boxPO->setTexture(*universe->textureManager->getTexture("picoTiles")->getTextureSheet());
    boxPO->setTextureRect(universe->textureManager->getTexture("picoTiles")->getTextureRect(box.getTileID()-1));
    boxPO->setPosition(sf::Vector2f(box.getPosition().x, box.getPosition().y));

    boxPO->acceleration = sf::Vector2f(0, .1);

    boxPO->createContinuousComputation("updateVelocity", updateVelocityBasedOnAcceleration(boxPO));
    boxPO->createContinuousComputation("updatePosition", updatePositionBasedOnVelocity(boxPO));

    std::map<std::string, CollisionShape*> boxCSs = {{"globalBounds", new CollisionShape(boxPO)}};

    std::vector<Entity*> boxEntityGroup = {new Entity{boxPO, boxCSs}};

    universe->entityManager->registerEntityGroup("boxes", boxEntityGroup);

    DebugEntity* boxDE = new DebugEntity(boxEntityGroup[0]);
    boxDE->customCollisionShapeBorderSettings["globalBounds"] = CollisionShapeBorderSettings{sf::Color::Green};
    universe->debugManager->registerDebugEntity(boxDE); // ? make it registerDebugEntityGroup for consistency
    //
    //
    //

    //
    //
    //



    //
    // Player
    //
    
    // Physical object
    PhysicalObject *playerPO = new PhysicalObject();
    playerPO->setPosition(sf::Vector2f(100, 50));
    playerPO->setTexture(*universe->textureManager->getTexture("knight")->getTextureSheet());
    playerPO->setTextureRect(universe->textureManager->getTexture("knight")->getTextureRect(9));
    
    playerPO->acceleration.y = .2; // gravity

    playerPO->createContinuousComputation("updateVelocity", updateVelocityBasedOnAcceleration(playerPO));
    playerPO->createContinuousComputation("updatePosition", updatePositionBasedOnVelocity(playerPO));
    //

    // Collision shape
    std::map<std::string, CollisionShape*> playerCSs;
    CollisionShape* playerCS = new CollisionShape(playerPO);
    playerCS->setSize(sf::Vector2f(playerPO->getGlobalBounds().width, 4));
    playerCS->offset = sf::Vector2f(0, 4);

    playerCSs["globalBounds"] = playerCS;
    //

    // Animation
    Animation* playerAnimation = new Animation(universe->textureManager->getTexture("knight"), playerPO, 9);
    playerAnimation->addTextureSequence("idle", std::vector<int>{9});
    playerAnimation->addTextureSequence("runRight", std::vector<int>{33, 34, 35});
    playerAnimation->addTextureSequence("runLeft", std::vector<int>{45, 46, 47});
    playerAnimation->setCurrentTextureSequence("idle");
    //

    // Build entity
    std::vector<Entity*> playerEntityGroup;
    playerEntityGroup.push_back(new Entity{playerPO, playerCSs, playerAnimation});
    //

    // Register player entity
    // 1 PhysicalObject, 1 CollisionShape, Animation present
    universe->entityManager->registerEntityGroup("player", playerEntityGroup);

    // Register debug entity
    DebugEntity* playerDE = new DebugEntity(playerEntityGroup[0]);
    playerDE->customCollisionShapeBorderSettings["globalBounds"] = CollisionShapeBorderSettings{sf::Color::Red};
    // Extra debug function example
    // playerDE->addExtraDebugFunction([playerPO](auto _){
    //     printf("%f, %f\n", playerPO->getPosition().x, playerPO->getPosition().y);
    // });

    universe->debugManager->registerDebugEntity(playerDE);
    //

    //
    //
    //



    //
    // Collision groups
    //

    // Player
    std::vector<CollisionShape*> playerCollisionGroup =  {playerEntityGroup[0]->collisionShapes["globalBounds"]};
    
    // Map
    std::vector<CollisionShape*> mapCollisionGroup;
    for(Entity* mapTileEntity : mapTilesEntityGroup){
        mapCollisionGroup.push_back(mapTileEntity->collisionShapes["globalBounds"]);
    }

    // Box
    std::vector<CollisionShape*> boxCollisionGroup = {boxEntityGroup[0]->collisionShapes["globalBounds"]};

    // Map tiles + Box for player AABB
    std::vector<CollisionShape*> tilesAndBoxCollisionGroup = mapCollisionGroup;
    tilesAndBoxCollisionGroup.insert(tilesAndBoxCollisionGroup.end(), boxCollisionGroup.begin(), boxCollisionGroup.end());

    // Map tiles + Player for box AABB
    std::vector<CollisionShape*> tilesAndPlayerCollisionGroup = mapCollisionGroup;
    tilesAndPlayerCollisionGroup.insert(tilesAndPlayerCollisionGroup.end(), playerCollisionGroup.begin(), playerCollisionGroup.end());

    //
    //
    //



    //
    // Collision management
    //

    // * Notes:
    // ! The collision shape CAN NOT be the initiator AND the recepient of the AABB response
    // ! To work properly, all AABB recipients with common initiator should be located in the SAME collision group

    
    universe->collisionManager->registerCollisionGroup("player", playerCollisionGroup);
    universe->collisionManager->registerCollisionGroup("tiles", mapCollisionGroup);
    universe->collisionManager->registerCollisionGroup("box", boxCollisionGroup);
    universe->collisionManager->registerCollisionGroup("tiles+box", tilesAndBoxCollisionGroup);
    universe->collisionManager->registerCollisionGroup("tiles+player", tilesAndPlayerCollisionGroup);
    // ? change collision pair to accept multiple groups, for convenience:
    // ? e.g.
    // ? createCollisionPair("name", vecInitiatorGroups{"g1name"}, vecRecipientGroups{"g2name", "g3name", "g4name"});
    // ? then loop through all initiator and recipient groups respectively when checking collisions
    // ?
    // ? to remove the need of creating extra collision groups like "tiles+box"



    // To work properly, all AABB shapes should be checked together
    universe->collisionManager->createCollisionPair("playerAABB", "player", "tiles+box");
    universe->collisionManager->setPairCollisionDetectionAlgorithm("playerAABB", boundingBox);
    universe->collisionManager->setPairCollisionResponse("playerAABB", "start_phase", [](std::vector<Collision> collisions){
        printf("start_phase\n");
    });
    universe->collisionManager->setPairCollisionResponse("playerAABB", "continuous_phase", [mapTilesEntityGroup, mapTilesDebugEntities](std::vector<Collision> collisions){
        printf("continuous_phase\n");
        resolveAABB(collisions);
        initiatorStandOnTopOfRecipient(collisions);
    });
    universe->collisionManager->setPairCollisionResponse("playerAABB", "end_phase", [mapTilesEntityGroup, mapTilesDebugEntities](std::vector<Collision> collisions){
        printf("end_phase\n");
    });


    // To work properly, all AABB shapes should be checked together
    universe->collisionManager->createCollisionPair("boxAABB", "box", "tiles");
    universe->collisionManager->setPairCollisionDetectionAlgorithm("boxAABB", boundingBox);
    universe->collisionManager->setPairCollisionResponse("boxAABB", "continuous_phase", [](std::vector<Collision> collisions){
        resolveAABB(collisions);
        initiatorStandOnTopOfRecipient(collisions);
    });



    universe->collisionManager->createCollisionPair("PB", "player", "box");
    universe->collisionManager->setPairCollisionDetectionAlgorithm("PB", boundingBox);
    universe->collisionManager->setPairCollisionResponse("PB", "start_phase", [boxDE](std::vector<Collision> collisions){
        boxDE->customCollisionShapeBorderSettings["globalBounds"] = CollisionShapeBorderSettings{sf::Color::Red};

        // Refactor as pushRecipient(float velocity);
        for(Collision collision : collisions){
            if(collision.recipientImpactSide == CollisionSide::right){
                collision.recipient->getOwner()->velocity.x = -10;
            }
            else if(collision.recipientImpactSide == CollisionSide::left){
                collision.recipient->getOwner()->velocity.x = 10;
            }
        }
    });
    universe->collisionManager->setPairCollisionResponse("PB", "end_phase", [boxDE](std::vector<Collision> collisions){
        boxDE->customCollisionShapeBorderSettings["globalBounds"] = CollisionShapeBorderSettings{sf::Color::Green};
        
        for(Collision collision : collisions){
            // TODO remove (minus) push force in the future
            collision.recipient->getOwner()->velocity.x = 0;
        }
    });

    //
    //
    //



    //
    // Controllers and events
    //

    universe->addController([playerPO, playerAnimation](){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            playerPO->velocity.x = -100;
            playerAnimation->setCurrentTextureSequence("runLeft");
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            playerPO->velocity.x = 100;
            playerAnimation->setCurrentTextureSequence("runRight");
        }
        else{
            playerPO->velocity.x = 0;
            playerAnimation->setCurrentTextureSequence("idle");
        }
    });

    universe->addEventHandler([playerPO](sf::Event event){
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
            playerPO->velocity.y = -100;
        }
    }); 

    //
    //
    //


    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    sf::View *view = new sf::View(sf::Vector2f(100, 100), sf::Vector2f(250, 150));
    
    window->setView(*view);
    window->setKeyRepeatEnabled(false); // For proper keyboard events handling (e.g. jumping)
    
    universe->setupWindow(window);
    
    universe->loop();

    return 0;
}