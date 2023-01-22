#include <iostream>

#include "Universe.h"


void Universe::addMap(std::vector<PhysicalObject*> *map){
    mapPtr = map;
}

void Universe::createPlayer(sf::Sprite *player){
    playerPtr = player;
}

void Universe::setupWindow(sf::RenderWindow *window){
    windowPtr = window;
}

void Universe::addController(const std::function<void (sf::Event event)> &lambdaController){
    controllers.push_back(lambdaController);
}

void Universe::addAnimation(Animation *animation){
    animations.push_back(animation);
}

void Universe::loop(){
    if(!windowPtr){
        printf("RenderWindow is not initialized. Use setupWindow method to initialize RenderWindow before(!) looping the Universe.\n");
        exit(1);
    }

    // Clocks initialization
    if(!animations.empty()){
        for(Animation *animation : animations){
            animation->restartClock();
        }
    }

    deltaClock.restart();
    //

    while(windowPtr->isOpen()){
        sf::Event event;
        while(windowPtr->pollEvent(event)){
            if (event.type == sf::Event::Closed) windowPtr->close();

            // Controllers
            for(std::function controller : controllers){
                controller(event);
            }
        }

        windowPtr->clear();

        // Calculate dt
        sf::Time deltaTime = deltaClock.restart();
        float dt = deltaTime.asSeconds();
        if(dt > 0.15f) dt = 0.15f;
        //


        // Game updates
        physicsManager.updatePhysics(dt);
        collisionManager.updateCollisions();

        if(!animations.empty()){
            for(Animation *animation : animations){
                animation->run();
            }
        }
        // 

        // Game draws
        for(sf::Sprite *tileSprite : *mapPtr){
            windowPtr->draw(*tileSprite);
        }
        
        if(playerPtr){
            windowPtr->draw(*playerPtr);
        }
        // 

        windowPtr->display();
    }
}