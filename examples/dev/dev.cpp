#include <stdio.h>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "../../SGE.hpp"

int main(){
    printf(".▄▄ ·  ▄▄ • ▄▄▄ .\n▐█ ▀. ▐█ ▀ ▪▀▄.▀·\n▄▀▀▀█▄▄█ ▀█▄▐▀▀▪▄\n▐█▄▪▐█▐█▄▪▐█▐█▄▄▌\n ▀▀▀▀ ·▀▀▀▀  ▀▀▀ \n");

    Universe *universe = new Universe();

    // Load all textures
    universe->textureManager.loadTexture(std::filesystem::current_path().string() + "/src/assets/pico_8_knight_sprite.png", "knight", TextureSheetSizes(8, 8, 12, 12));
    universe->textureManager.loadTexture(std::filesystem::current_path().string() + "/src/assets/pico_8_tiles.png", "picoTiles", TextureSheetSizes(8, 8, 12, 12));
    //

    std::string s = std::filesystem::current_path().string() + "/src/assets/map.json";

    // Map
    // TODO init in / add to Scene in the future (?)
    tmx::Map map;
    if(!map.load(std::filesystem::current_path().string() + "/src/assets/map.tmx")){
        printf("Can't load map");
        exit(1);
    }

    const auto& layers = map.getLayers();
    const auto& tiles = layers[0]->getLayerAs<tmx::TileLayer>().getTiles();

    std::vector<PhysicalObject*> mapTiles;

    for(int i = 0; i < map.getTileCount().y; i++){
        for(int j = 0; j < map.getTileCount().x; j++){
            if(tiles[map.getTileCount().x*i+j].ID != 0){
                PhysicalObject *tile = new PhysicalObject();
                tile->setIsFlying(true);

                tile->setTexture(*universe->textureManager.getTexture("picoTiles")->getTextureSheet());
                tile->setTextureRect(universe->textureManager.getTexture("picoTiles")->getTextureRect(tiles[map.getTileCount().x*i+j].ID-1));
                tile->setPosition(sf::Vector2f(j*map.getTileSize().x, i*map.getTileSize().y));
                mapTiles.push_back(tile);
            }
        }
    }
    
    universe->addMap(&mapTiles);
    // 

    // Player
    PhysicalObject *player = new PhysicalObject();
    player->setMass(100);
    player->setPosition(sf::Vector2f(100, 50));

    player->createFlag("canJump");

    player->createAction("jumpStart", [player](){
        player->setIsFlying(true);
        player->setVelocityGoalY(-300);

        player->setFlag("canJump", false);
    });

    player->createAction("jumpReset", [player](){
        player->setFlag("canJump", true);
    });

    player->createConditionalAction("jumpFall",
        [player](){
            return player->getMovementVector().y <= -300;
        },
        [player](){
            player->setIsFlying(false);
        }
    );

    universe->createPlayer(player);
    universe->physicsManager.addPhysicalObject(player);
    //

    // Player animation
    Animation *playerAnimation = new Animation(universe->textureManager.getTexture("knight"), player, 9);
    playerAnimation->addAnimationSequence("idle", std::vector<int>{9});
    playerAnimation->addAnimationSequence("runRight", std::vector<int>{33, 34, 35});
    playerAnimation->addAnimationSequence("runLeft", std::vector<int>{45, 46, 47});
    playerAnimation->setCurrentAnimationSequence("idle");

    universe->textureManager.registerAnimation(playerAnimation);
    //

    // * CollisionManager
    CollisionShape *playerCollisionShape = new CollisionShape(player);

    std::vector<CollisionShape*> mapTileCollisionShapes;
    for(PhysicalObject *tile : mapTiles){
        CollisionShape *tileCS = new CollisionShape(tile);
        mapTileCollisionShapes.push_back(tileCS);
    }


    universe->collisionManager.registerCollisionGroup("player", new CollisionGroup{CollisionGroupType::moveable, std::vector<CollisionShape*>{playerCollisionShape}});
    universe->collisionManager.registerCollisionGroup("tiles", new CollisionGroup{CollisionGroupType::solid, mapTileCollisionShapes});
    universe->collisionManager.createCollisionPair("PTCollisionPair", "player", "tiles");
    universe->collisionManager.setCollisionDetectionAlgorithm("PTCollisionPair", boundingBox);

    universe->collisionManager.addCollisionResponse("PTCollisionPair", resolveAABB);
    universe->collisionManager.addCollisionResponse("PTCollisionPair", [player](std::vector<Collision> collisions){
        player->doAction("jumpReset");
    });
    // *

    // TODO use movement functions on player PhysicalObject
    universe->addController([player, playerAnimation](){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            player->setVelocityGoalX(-100);
            playerAnimation->setCurrentAnimationSequence("runLeft");
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            player->setVelocityGoalX(100);
            playerAnimation->setCurrentAnimationSequence("runRight");
        }
        else{
            player->setVelocityGoalX(0);
            playerAnimation->setCurrentAnimationSequence("idle");
        }
    });
    universe->addEventHandler([player](sf::Event event){
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
            if(player->getFlag("canJump")){
                player->doAction("jumpStart");
            }
        }
    });

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