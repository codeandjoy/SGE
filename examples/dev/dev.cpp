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
    universe->textureManager->loadTexture(std::filesystem::current_path().string() + "/examples/dev/assets/pico_8_knight_sprite.png", "knight", TextureSheetSizes(8, 8, 12, 12));
    universe->textureManager->loadTexture(std::filesystem::current_path().string() + "/examples/dev/assets/pico_8_tiles.png", "picoTiles", TextureSheetSizes(8, 8, 12, 12));
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
    //

    // Collision shape
    std::map<std::string, CollisionShape*> playerCSs;
    CollisionShape* playerCS = new CollisionShape(playerPO);
    playerCS->setSize(sf::Vector2f(playerPO->getGlobalBounds().width, 4));
    playerCS->setOffset(sf::Vector2f(0, 4));

    playerCSs["globalBounds"] = playerCS;
    //

    // Animation
    Animation* playerAnimation = new Animation(universe->textureManager->getTexture("knight"), playerPO, 9);
    playerAnimation->addAnimationSequence("idle", std::vector<int>{9});
    playerAnimation->addAnimationSequence("runRight", std::vector<int>{33, 34, 35});
    playerAnimation->addAnimationSequence("runLeft", std::vector<int>{45, 46, 47});
    playerAnimation->setCurrentAnimationSequence("idle");
    //

    // Build entity
    std::vector<Entity*> playerEntityGroup;
    playerEntityGroup.push_back(new Entity{playerPO, playerCSs, playerAnimation});
    //

    // Register player entity
    // 1 PhysicalObject, 1 CollisionShape, Animation present
    universe->entityManager->registerEntityGroup("playerPhysicalObject", playerEntityGroup);
    universe->debugManager->registerDebugEntity(new DebugEntity(playerEntityGroup[0]));
    //

    //
    //
    //



    //
    // Collision groups
    //

    // PlayerPhysicalObject
    std::vector<CollisionShape*> playerCollisionShapesVec =  {playerEntityGroup[0]->collisionShapes["globalBounds"]};
    CollisionGroup* playerCollisionGroup = new CollisionGroup{CollisionGroupType::moveable, playerCollisionShapesVec, playerEntityGroup};
    //
    
    // Map
    std::vector<CollisionShape*> mapCollisionShapes;
    for(Entity* mapTileEntity : mapTilesEntityGroup){
        mapCollisionShapes.push_back(mapTileEntity->collisionShapes["globalBounds"]);
    }

    CollisionGroup* mapTilesCollisionGroup = new CollisionGroup{CollisionGroupType::solid, mapCollisionShapes, mapTilesEntityGroup};
    //

    //
    //
    //



    //
    // Collision management
    //
    
    universe->collisionManager->registerCollisionGroup("player", playerCollisionGroup);
    universe->collisionManager->registerCollisionGroup("tiles", mapTilesCollisionGroup);

    universe->collisionManager->createCollisionPair("PTCollisionPair", "player", "tiles");
    universe->collisionManager->setCollisionDetectionAlgorithm("PTCollisionPair", boundingBox);

    universe->collisionManager->addCollisionResponse("PTCollisionPair", resolveAABB);
    universe->collisionManager->addCollisionResponse("PTCollisionPair", [playerPO](std::vector<Collision> collisions){
        playerPO->velocity.y = 0;
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
            playerAnimation->setCurrentAnimationSequence("runLeft");
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            playerPO->velocity.x = 100;
            playerAnimation->setCurrentAnimationSequence("runRight");
        }
        else{
            playerPO->velocity.x = 0;
            playerAnimation->setCurrentAnimationSequence("idle");
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