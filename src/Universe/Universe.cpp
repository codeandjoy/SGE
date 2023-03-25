#include "Universe.h"


void Universe::setupWindow(sf::RenderWindow *window){
    windowPtr = window;
}

void Universe::addController(std::function<void()> controller){
    controllers.push_back(controller);
}

void Universe::addEventHandler(std::function<void(sf::Event event)> eventHandler){
    eventHandlers.push_back(eventHandler);
}

void Universe::loop(){
    if(!windowPtr){
        printf("RenderWindow is not initialized. Use setupWindow method to initialize RenderWindow before(!) looping the Universe.\n");
        exit(1);
    }

    // Clocks initialization
    // ! Remove in the future (init on animation creation?)
    textureManager.initAnimationClocks();
    // !

    deltaClock.restart();
    //

    while(windowPtr->isOpen()){
        sf::Event event;
        while(windowPtr->pollEvent(event)){
            if (event.type == sf::Event::Closed) windowPtr->close();
        
            for(std::function eventHandler : eventHandlers){
                eventHandler(event);
            }
        }

        // Controllers
        for(std::function controller : controllers){
            controller();
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
        textureManager.updateAnimations();
        // 

        // Game draws
        for(sf::Sprite *tileSprite : *mapPtr){
            windowPtr->draw(*tileSprite);
        }
        
        if(playerPtr){
            windowPtr->draw(*playerPtr);
        }

        for(auto& [key, collisionGroup] : collisionManager.getCollisionGroups()){
            for(CollisionShape *collisionShape : collisionGroup->collisionShapes){
                if(collisionShape->getIsVisible()){
                    windowPtr->draw(*collisionShape);
                }
            }
        }
        // 

        windowPtr->display();
    }
}

void Universe::addMap(std::vector<PhysicalObject*> *map){
    mapPtr = map;
}

void Universe::createPlayer(sf::Sprite *player){
    playerPtr = player;
}