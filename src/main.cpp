#include <stdio.h>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "Universe.h"
#include "TextureManager.h"
#include "TextureSheet.h"
#include "TextureSheetSizes.h"
#include "Animation.h"
#include "PhysicsManager.h"
#include "PhysicalObject.h"
#include "CollisionGroupType.h"
#include "CollisionDetectionAlgorithms.h"
#include "CollisionResponses.h"


int main(){
    printf(".▄▄ ·  ▄▄ • ▄▄▄ .\n▐█ ▀. ▐█ ▀ ▪▀▄.▀·\n▄▀▀▀█▄▄█ ▀█▄▐▀▀▪▄\n▐█▄▪▐█▐█▄▪▐█▐█▄▄▌\n ▀▀▀▀ ·▀▀▀▀  ▀▀▀ \n");

    Universe *universe = new Universe();

    // Load all textures
    TextureManager *textureManager = new TextureManager();
    textureManager->load(std::filesystem::current_path().string() + "/src/assets/pico_8_knight_sprite.png", TextureSheetSizes(8, 8, 12, 12), "knight");
    textureManager->load(std::filesystem::current_path().string() + "/src/assets/pico_8_tiles.png", TextureSheetSizes(8, 8, 12, 12), "picoTiles");
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

                tile->setTexture(*textureManager->get("picoTiles")->getTextureSheet());
                tile->setTextureRect(textureManager->get("picoTiles")->getTextureRect(tiles[map.getTileCount().x*i+j].ID-1));
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
    player->createAction("jump", [](){
        printf("Jumping\n");
    });
    universe->createPlayer(player);
    universe->physicsManager.addPhysicalObject(player);
    //

    // Player animation
    Animation *playerAnimation = new Animation(textureManager->get("knight"), player, 9);
    playerAnimation->addAnimationSequence("idle", std::vector<int>{9});
    playerAnimation->addAnimationSequence("runRight", std::vector<int>{33, 34, 35});
    playerAnimation->addAnimationSequence("runLeft", std::vector<int>{45, 46, 47});
    playerAnimation->setCurrentAnimationSequence("idle");

    universe->addAnimation(playerAnimation);
    //

    // CollisionManager
    universe->collisionManager.createCollisionGroup("player", CollisionGroupType::moveable, std::vector<PhysicalObject*>{player});
    universe->collisionManager.createCollisionGroup("tiles", CollisionGroupType::solid, mapTiles);
    universe->collisionManager.createCollisionPair("PTCollisionPair", "player", "tiles");
    universe->collisionManager.setCollisionDetectionAlgorithm("PTCollisionPair", boundingBox);

    universe->collisionManager.addCollisionResponse("PTCollisionPair", repel);
    //

    // TODO use movement functions on player PhysicalObject
    universe->addController([player, playerAnimation](){
        // ! TODO CHANGE TO ISKEYPRESSED !
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            player->setVelocityGoalX(-100);
            playerAnimation->setCurrentAnimationSequence("runLeft");
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            player->setVelocityGoalX(100);
            playerAnimation->setCurrentAnimationSequence("runRight");
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            player->doAction("jump");
        }
        else{
            player->setVelocityGoalX(0);
            playerAnimation->setCurrentAnimationSequence("idle");
        }
    });

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Test", sf::Style::Fullscreen);
    sf::View *view = new sf::View(sf::Vector2f(50, 50), sf::Vector2f(480, 270));
    window->setView(*view);
    universe->setupWindow(window);
    
    universe->loop();

    return 0;
}