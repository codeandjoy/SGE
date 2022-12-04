#include <SFML/Graphics.hpp>
using namespace sf;

#include "universe.h"



Universe::Universe(RenderWindow &window){
    windowPtr = &window;
}

void Universe::loop(){
    while(windowPtr->isOpen()){
        Event event;
        while(windowPtr->pollEvent(event)){
            if (event.type == Event::Closed) windowPtr->close();

            // Controllers

        }

        // Game updates/draws
    }
}