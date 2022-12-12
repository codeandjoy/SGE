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

    RenderWindow *window = new RenderWindow(VideoMode(1200, 800), "Test", Style::Fullscreen);
    universe->setupWindow(*window);
    
    universe->loop();

    return 0;
}