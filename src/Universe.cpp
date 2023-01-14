#include <iostream>

#include <jsoncpp/json/json.h>

#include "Universe.h"
#include "./utils/readTiledMapData.h"


void Universe::addMap(std::vector<sf::Sprite*> *map){
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

    if(!animations.empty()){
        for(Animation *animation : animations){
            animation->restartClock();
        }
    }

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

        // Game updates
        physicsManager.updatePhysics();
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
        
        if(!playerPtr){
            printf("Player is not setup");
        }
        else{
            windowPtr->draw(*playerPtr);
        }

        // Draw solid object's collision rects if set
        if(physicsManager.drawCollideRects){
            for(SolidObject *sObject : *physicsManager.getSolidObjects()){
                windowPtr->draw(*sObject->getCollisionRect());
            }
        }
        // 

        windowPtr->display();
    }
}