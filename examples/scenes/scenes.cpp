#include <filesystem>
#include "../../SGE.hpp"
#include "./player/setupPlayerEntity.h"
#include "./scene_1/setupScene1.h"
#include "./scene_2/setupScene2.h"


int main(){
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000, 600), "CollisionPhase");
    window->setKeyRepeatEnabled(false);
    sf::View* view = new sf::View(sf::Vector2f(100, 70), sf::Vector2f(250, 150));

    sge::Universe* universe = new sge::Universe(window);

    universe->assetsManager->loadTextureSheet(
        std::filesystem::current_path().string() + "/examples/scenes/assets/pico_8_tiles.png",
        "picoTiles",
        sge::TextureSheetSizes{8, 8, 12, 12}
    );
    universe->assetsManager->loadTextureSheet(
        std::filesystem::current_path().string() + "/examples/scenes/assets/pico_8_knight_sprite.png",
        "knight",
        sge::TextureSheetSizes{8, 8, 12, 12}
    );

    // Player is universal for all scenes
    sge::Entity* playerEntity = setupPlayerEntity(universe);

    sge::Scene* scene_1 = setupScene1(universe, playerEntity, view);
    sge::Scene* scene_2 = setupScene2(universe, playerEntity, view);

    universe->drumSceneManager->registerComponent("level_1", scene_1);
    universe->drumSceneManager->registerComponent("level_2", scene_2);
    
    universe->drumSceneManager->setCurrentScene("level_1");



    universe->controllerManager->registerComponent([playerEntity](sf::Event event){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            playerEntity->physicalObject->velocity.x = -70;
            playerEntity->animation->setCurrentTextureSequence("runLeft");
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            playerEntity->physicalObject->velocity.x = 70;
            playerEntity->animation->setCurrentTextureSequence("runRight");
        }
        else{
            playerEntity->physicalObject->velocity.x = 0;
            playerEntity->animation->setCurrentTextureSequence("idle");
        }

        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
            playerEntity->physicalObject->velocity.y = -120;
        }
    }); 



    
    
    universe->loop();
    return 0;
}