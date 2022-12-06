#include <SFML/Graphics.hpp>
#include <stdio.h>
using namespace sf;

#include "universe.h"

int main(){
    Universe *universe = new Universe();
    universe->createMap("./map/map.tmj");

    RenderWindow *window = new RenderWindow(VideoMode(1200, 800), "Test", Style::Fullscreen);
    universe->setupWindow(*window);
    
    universe->loop();

    return 0;
}