#include <stdio.h>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "Universe.h"
#include "Spritesheet.h"
#include "Animation.h"
#include "PhysicalObject.h"
#include "Gravity.h"

int main(){
    Universe *universe = new Universe();
    universe->createMap(std::filesystem::current_path().string() + "/src/assets/map.tmj");

    Spritesheet *knightSpritesheet = new Spritesheet(8, 8, 12, 12, std::filesystem::current_path().string() + "/src/assets/pico_8_knight_sprite.png");

    Entity *player = new Entity();
    universe->createPlayer(player);

    // Player animation
    Animation *playerAnimation = new Animation(knightSpritesheet, player, 9);
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