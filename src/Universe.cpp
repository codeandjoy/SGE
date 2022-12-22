#include <iostream>

#include <jsoncpp/json/json.h>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

#include "Universe.h"
#include "./utils/readTiledMapData.h"



void Universe::createMap(const string mapDataFileLocation){
    // TODO map borders == map size
    Json::Value mapData = readTiledMapData(mapDataFileLocation);
    
    int mapWidth = mapData["width"].asInt();
    int mapHeight = mapData["height"].asInt();
    int tileWidth = mapData["tilewidth"].asInt();
    int tileHeight = mapData["tileheight"].asInt();

    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapWidth; j++){
            if(mapData["layers"][0]["data"][mapWidth*i+j].asInt() == 1){
                RectangleShape block(Vector2f(tileWidth, tileHeight));
                block.setPosition(Vector2f(j*tileWidth, i*tileHeight));

                map.push_back(block);
            }
        }
    }
}

void Universe::createPlayer(Entity &player){
    playerPtr = &player;
}

void Universe::setupWindow(RenderWindow &window){
    windowPtr = &window;
}

void Universe::addController(const function<void (Event event)> &lambdaController){
    controllers.push_back(lambdaController);
}

void Universe::addPhysicalObject(PhysicalObject *physicalObject){
    physicalObjects.push_back(physicalObject);
}

void Universe::loop(){
    if(!windowPtr){
        printf("RenderWindow is not initialized. Use setupWindow method to initialize RenderWindow before(!) looping the Universe.\n");
        exit(1);
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
        playerPtr->update();

        for(PhysicalObject *pObject : physicalObjects){
            pObject->updatePhysics();
        }
        // 

        // Game draws
        for(RectangleShape &block : map){
            windowPtr->draw(block);
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