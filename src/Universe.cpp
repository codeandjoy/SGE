#include <iostream>

#include <jsoncpp/json/json.h>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

#include "Universe.h"
#include "./utils/readTiledMapData.h"


void Universe::addMap(std::vector<sf::Sprite> *map){
    mapPtr = map;
}

void Universe::createPlayer(Entity *player){
    playerPtr = player;
}

void Universe::setupWindow(RenderWindow *window){
    windowPtr = window;
}

void Universe::addController(const function<void (Event event)> &lambdaController){
    controllers.push_back(lambdaController);
}

void Universe::addPhysicalObject(PhysicalObject *physicalObject){
    physicalObjects.push_back(physicalObject);
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
        Event event;
        while(windowPtr->pollEvent(event)){
            if (event.type == Event::Closed) windowPtr->close();

            // Controllers
            for(function controller : controllers){
                controller(event);
            }
        }

        windowPtr->clear();

        // Game updates
        if(playerPtr){
            playerPtr->update();
        }

        if(!physicalObjects.empty()){
            for(PhysicalObject *pObject : physicalObjects){
                pObject->updatePhysics();
            }
        }

        if(!animations.empty()){
            for(Animation *animation : animations){
                animation->run();
            }
        }
        // 

        // Game draws
        for(sf::Sprite tileSprite : *mapPtr){
            windowPtr->draw(tileSprite);
        }

        if(!playerPtr){
            printf("Player is not setup");
        }
        else{
            windowPtr->draw(*playerPtr);
        }
        // 

        windowPtr->display();
    }
}