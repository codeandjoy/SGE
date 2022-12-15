#include <stdio.h>
#include <filesystem>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

#include "universe.h"

int main(){
    Universe *universe = new Universe();
    universe->createMap(filesystem::current_path().string() + "/src/map/map.tmj");

    Entity *player = new Entity();
    universe->createPlayer(*player);

    universe->addController([player](Event event){
        if(event.type == Event::KeyPressed){
            if(event.key.code == Keyboard::D) player->setIsMovingRight(true);
            if(event.key.code == Keyboard::A) player->setIsMovingLeft(true);
        }
        if(event.type == Event::KeyReleased){
            if(event.key.code == Keyboard::D) player->setIsMovingRight(false);
            if(event.key.code == Keyboard::A) player->setIsMovingLeft(false);
        }
    });

    RenderWindow *window = new RenderWindow(VideoMode::getDesktopMode(), "Test", Style::Fullscreen);
    View *view = new View(Vector2f(50, 50), Vector2f(480, 270));
    window->setView(*view);
    universe->setupWindow(*window);
    
    universe->loop();

    return 0;
}