#include <stdio.h>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "../../SGE.hpp"

int main(){
    printf(".▄▄ ·  ▄▄ • ▄▄▄ .\n▐█ ▀. ▐█ ▀ ▪▀▄.▀·\n▄▀▀▀█▄▄█ ▀█▄▐▀▀▪▄\n▐█▄▪▐█▐█▄▪▐█▐█▄▄▌\n ▀▀▀▀ ·▀▀▀▀  ▀▀▀ \n");



    // * Init
    PhysicsManager* physicsManager = new PhysicsManager();
    CollisionManager* collisionManager = new CollisionManager();
    TextureManager* textureManager = new TextureManager();
    EntityManager* entityManager = new EntityManager(physicsManager, collisionManager, textureManager);

    Universe *universe = new Universe(physicsManager, collisionManager, textureManager, entityManager);
    // *



    // * Load all textures
    universe->textureManager->loadTexture(std::filesystem::current_path().string() + "/src/assets/pico_8_knight_sprite.png", "knight", TextureSheetSizes(8, 8, 12, 12));
    universe->textureManager->loadTexture(std::filesystem::current_path().string() + "/src/assets/pico_8_tiles.png", "picoTiles", TextureSheetSizes(8, 8, 12, 12));
    // *



    // *
    // * Map
    // *

    // * Read
    tmx::Map map;
    if(!map.load(std::filesystem::current_path().string() + "/src/assets/map.tmx")){
        printf("Can't load map");
        exit(1);
    }

    const auto& layers = map.getLayers();
    const auto& tiles = layers[0]->getLayerAs<tmx::TileLayer>().getTiles();
    // *

    // * Init EntityGroup
    std::vector<Entity*> mapTilesEntityGroup;
    // *

    // * Physical objects
    std::vector<PhysicalObject*> mapTilesPhysicalObjects;

    for(int i = 0; i < map.getTileCount().y; i++){
        for(int j = 0; j < map.getTileCount().x; j++){
            if(tiles[map.getTileCount().x*i+j].ID != 0){
                PhysicalObject *tile = new PhysicalObject();
                tile->setIsFlying(true);

                tile->setTexture(*universe->textureManager->getTexture("picoTiles")->getTextureSheet());
                tile->setTextureRect(universe->textureManager->getTexture("picoTiles")->getTextureRect(tiles[map.getTileCount().x*i+j].ID-1));
                tile->setPosition(sf::Vector2f(j*map.getTileSize().x, i*map.getTileSize().y));
                mapTilesPhysicalObjects.push_back(tile);
            }
        }
    }
    // *

    // * Init Entities and their physical objects
    for(PhysicalObject* physicalObject : mapTilesPhysicalObjects){
        mapTilesEntityGroup.push_back(new Entity{physicalObject});
    }
    // *

    // * Collision shapes
    // Each tile entity has 1 collision shape ("globalBounds")
    for(int i = 0; i < mapTilesEntityGroup.size(); i++){
        mapTilesEntityGroup[i]->collisionShapes = std::map<std::string, CollisionShape*>{{"globalBounds", new CollisionShape(mapTilesPhysicalObjects[i])}};
    }
    // *

    // * Register map tile entities
    // 1 PhysicalObject, 1 CollisionShape, no Animation
    universe->entityManager->registerEntityGroup("mapTiles", mapTilesEntityGroup);
    // *

    // *
    // *
    // *



    // *
    // * Player
    // *
    
    // * Physical object
    PhysicalObject *playerPhysicalObject = new PhysicalObject();
    playerPhysicalObject->setMass(100);
    playerPhysicalObject->setPosition(sf::Vector2f(100, 50));

    playerPhysicalObject->createFlag("canJump");

    playerPhysicalObject->createAction("jumpStart", [playerPhysicalObject](){
        playerPhysicalObject->setIsFlying(true);
        playerPhysicalObject->setVelocityGoalY(-300);

        playerPhysicalObject->setFlag("canJump", false);
    });

    playerPhysicalObject->createAction("jumpReset", [playerPhysicalObject](){
        playerPhysicalObject->setFlag("canJump", true);
    });

    playerPhysicalObject->createConditionalAction("jumpFall",
        [playerPhysicalObject](){
            return playerPhysicalObject->getMovementVector().y <= -300;
        },
        [playerPhysicalObject](){
            playerPhysicalObject->setIsFlying(false);
        }
    );
    // *

    // * Collision shape
    std::map<std::string, CollisionShape*> playerCollisionShapes;
    playerCollisionShapes["globalBounds"] = new CollisionShape(playerPhysicalObject);    
    // *

    // * Animation
    Animation* playerAnimation = new Animation(universe->textureManager->getTexture("knight"), playerPhysicalObject, 9);
    playerAnimation->addAnimationSequence("idle", std::vector<int>{9});
    playerAnimation->addAnimationSequence("runRight", std::vector<int>{33, 34, 35});
    playerAnimation->addAnimationSequence("runLeft", std::vector<int>{45, 46, 47});
    playerAnimation->setCurrentAnimationSequence("idle");
    // *

    // * Entity
    std::vector<Entity*> playerEntityGroup;
    playerEntityGroup.push_back(new Entity{playerPhysicalObject, playerCollisionShapes, playerAnimation});
    // *

    universe->entityManager->registerEntityGroup("playerPhysicalObject", playerEntityGroup); // ? Pass vector by reference ?
    // *
    // *
    // *



    // *
    // * Collision groups
    // *

    // * PlayerPhysicalObject
    std::vector<CollisionShape*> playerCollisionShapesVec =  {playerEntityGroup[0]->collisionShapes["globalBounds"]};
    CollisionGroup* playerCollisionGroup = new CollisionGroup{CollisionGroupType::moveable, playerCollisionShapesVec, playerEntityGroup};
    // *
    
    // * Map
    std::vector<CollisionShape*> mapCollisionShapes;
    for(Entity* mapTileEntity : mapTilesEntityGroup){
        mapCollisionShapes.push_back(mapTileEntity->collisionShapes["globalBounds"]);
    }

    CollisionGroup* mapTilesCollisionGroup = new CollisionGroup{CollisionGroupType::solid, mapCollisionShapes, mapTilesEntityGroup};
    // *

    // *
    // *
    // *



    // *
    // * Collision management
    // *
    
    universe->collisionManager->registerCollisionGroup("playerPhysicalObject", playerCollisionGroup);
    universe->collisionManager->registerCollisionGroup("tiles", mapTilesCollisionGroup);

    universe->collisionManager->createCollisionPair("PTCollisionPair", "playerPhysicalObject", "tiles");
    universe->collisionManager->setCollisionDetectionAlgorithm("PTCollisionPair", boundingBox);

    universe->collisionManager->addCollisionResponse("PTCollisionPair", resolveAABB);
    universe->collisionManager->addCollisionResponse("PTCollisionPair", [playerPhysicalObject](std::vector<Collision> collisions){
        playerPhysicalObject->doAction("jumpReset");
    });

    // *
    // *
    // *


    // *
    // * Controllers and events
    // *

    universe->addController([playerPhysicalObject, playerAnimation](){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            playerPhysicalObject->setVelocityGoalX(-100);
            playerAnimation->setCurrentAnimationSequence("runLeft");
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            playerPhysicalObject->setVelocityGoalX(100);
            playerAnimation->setCurrentAnimationSequence("runRight");
        }
        else{
            playerPhysicalObject->setVelocityGoalX(0);
            playerAnimation->setCurrentAnimationSequence("idle");
        }
    });
    universe->addEventHandler([playerPhysicalObject](sf::Event event){
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
            if(playerPhysicalObject->getFlag("canJump")){
                playerPhysicalObject->doAction("jumpStart");
            }
        }
    });

    // *
    // *
    // *


    // sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Test", sf::Style::Fullscreen);
    // sf::View *view = new sf::View(sf::Vector2f(50, 50), sf::Vector2f(480, 270));
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    sf::View *view = new sf::View(sf::Vector2f(100, 100), sf::Vector2f(250, 150));
    window->setView(*view);

    window->setKeyRepeatEnabled(false); // for proper keyboard events handling (like jumping)
    
    universe->setupWindow(window);
    
    universe->loop();

    return 0;
}