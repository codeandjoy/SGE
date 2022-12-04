#include <SFML/Graphics.hpp>
using namespace sf;

#include "universe.h"

int main(){
    RenderWindow window(VideoMode(1200, 800), "Test", Style::Fullscreen);

    Universe *universe = new Universe(window);

    universe->loop();

    return 0;
}