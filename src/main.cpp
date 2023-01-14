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
#include "SolidObject.h"
#include "Moveable.h"
#include "Gravity.h"
#include "CollisionGroupType.h"


int main(){
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

    std::vector<sf::Sprite*> mapTiles;

    for(int i = 0; i < map.getTileCount().y; i++){
        for(int j = 0; j < map.getTileCount().x; j++){
            if(tiles[map.getTileCount().x*i+j].ID != 0){
                sf::Sprite *tile = new sf::Sprite();
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
    sf::Sprite *player = new sf::Sprite();
    player->setPosition(sf::Vector2f(100, 50));
    universe->createPlayer(player);
    //

    // Player animation
    Animation *playerAnimation = new Animation(textureManager->get("knight"), player, 9);
    playerAnimation->addAnimationSequence("idle", std::vector<int>{9});
    playerAnimation->addAnimationSequence("runRight", std::vector<int>{33, 34, 35});
    playerAnimation->addAnimationSequence("runLeft", std::vector<int>{45, 46, 47});
    playerAnimation->setCurrentAnimationSequence("idle");

    universe->addAnimation(playerAnimation);
    //

    // PhysicsManager
    universe->physicsManager.drawCollideRects = true; // TODO move to CollisionManager

    PhysicalObject *playerPhy = new PhysicalObject(player);
    Moveable *playerMoveable = new Moveable(); // ? set veloctiy here ?
    Gravity *playerGravity = new Gravity(sf::Vector2f(0, .1));
    
    playerPhy->addPhysicalProperty(playerMoveable);
    playerPhy->addPhysicalProperty(playerGravity);
    
    universe->physicsManager.addPhysicalObject(playerPhy);
    //

    // CollisionManager
    universe->collisionManager.createCollisionGroup("player", CollisionGroupType::moveable, std::vector<sf::Sprite*>{player});
    universe->collisionManager.createCollisionGroup("tiles", CollisionGroupType::solid, mapTiles);
    universe->collisionManager.createCollisionPair("PTCollisionPair", "player", "tiles");
    int counter = 0;
    universe->collisionManager.addCollisionResponse("PTCollisionPair", [&counter](){
        printf("COLLISION%d\n", counter);
        counter++;
    });
    //

    universe->addController([playerMoveable, playerAnimation](sf::Event event){
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::D){
                playerMoveable->setIsMovingRight(true);
                playerAnimation->setCurrentAnimationSequence("runRight");
            }
            if(event.key.code == sf::Keyboard::A){
                playerMoveable->setIsMovingLeft(true);
                playerAnimation->setCurrentAnimationSequence("runLeft");
            }
        }
        if(event.type == sf::Event::KeyReleased){
            if(event.key.code == sf::Keyboard::D) playerMoveable->setIsMovingRight(false);
            if(event.key.code == sf::Keyboard::A) playerMoveable->setIsMovingLeft(false);
            
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