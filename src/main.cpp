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
#include "PhysicalObject.h"
#include "Gravity.h"


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

    std::vector<sf::Sprite> mapTiles; // just sprites, not pointers

    for(int i = 0; i < map.getTileCount().y; i++){
        for(int j = 0; j < map.getTileCount().x; j++){
            sf::Sprite tile;
            tile.setTexture(*textureManager->get("picoTiles")->getTextureSheet());
            tile.setTextureRect(textureManager->get("picoTiles")->getTextureRect(tiles[map.getTileCount().x*i+j].ID-1));
            tile.setPosition(sf::Vector2f(j*map.getTileSize().x, i*map.getTileSize().y));
            mapTiles.push_back(tile);
        }
    }
    
    universe->addMap(&mapTiles);
    // 

    // Player
    Entity *player = new Entity();
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

    // // Player physics
    // PhysicalObject *playerPhy = new PhysicalObject(player);
    // PhysicalProperty *entityGravity = new Gravity(sf::Vector2f(0, 0.1));
    // playerPhy->addPhysicalProperty(entityGravity);

    // universe->addPhysicalObject(playerPhy);
    // // 

    universe->addController([player, playerAnimation](sf::Event event){
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::D){
                player->setIsMovingRight(true);
                playerAnimation->setCurrentAnimationSequence("runRight");
            }
            if(event.key.code == sf::Keyboard::A){
                player->setIsMovingLeft(true);
                playerAnimation->setCurrentAnimationSequence("runLeft");
            }
        }
        if(event.type == sf::Event::KeyReleased){
            if(event.key.code == sf::Keyboard::D) player->setIsMovingRight(false);
            if(event.key.code == sf::Keyboard::A) player->setIsMovingLeft(false);
            
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