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
        RectangleShape *block = new RectangleShape(Vector2f(200, 200));
        block->setPosition(Vector2f(10,10));
        block->setOutlineColor(Color::Red);

        windowPtr->draw(*block);
    
        windowPtr->display();
    }
}