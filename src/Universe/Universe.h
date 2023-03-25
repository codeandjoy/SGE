#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include "../Physics/PhysicsManager.h"
#include "../Physics/PhysicalObject.h"
#include "../Collision/CollisionManager.h"
#include "../Texture/TextureManager.h"


class Universe{
    public:
        void setupWindow(sf::RenderWindow *window);

        void addController(std::function<void()> controller);
        void addEventHandler(std::function<void(sf::Event event)> eventHandler);

        void loop();

        PhysicsManager physicsManager;
        CollisionManager collisionManager;
        TextureManager textureManager;

        // ! remove
        void createPlayer(sf::Sprite *player);
        void addMap(std::vector<PhysicalObject*> *map); // TODO managed in Scene in the future(?)

    private:
        sf::RenderWindow *windowPtr;

        sf::Clock deltaClock;
        
        std::vector<std::function<void()>> controllers;
        std::vector<std::function<void(sf::Event event)>> eventHandlers;
        
        // ! remove
        sf::Sprite *playerPtr; // ! for drawing
        std::vector<PhysicalObject*> *mapPtr; // ! for drawing
};


#endif