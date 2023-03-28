#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include "../Physics/PhysicsManager.h"
#include "../Physics/PhysicalObject.h"
#include "../Collision/CollisionManager.h"
#include "../Texture/TextureManager.h"
#include "../Entity/EntityManager.h"

class Universe{
    public:
        Universe(PhysicsManager* _physicsManager, CollisionManager* _collisionManager, TextureManager* _textureManager, EntityManager* _entityManager);

        void setupWindow(sf::RenderWindow *window);

        void addController(std::function<void()> controller);
        void addEventHandler(std::function<void(sf::Event event)> eventHandler);

        void loop();

        PhysicsManager* physicsManager;
        CollisionManager* collisionManager;
        TextureManager* textureManager;
        EntityManager* entityManager;

    private:
        sf::RenderWindow *windowPtr;

        sf::Clock deltaClock;
        
        std::vector<std::function<void()>> controllers;
        std::vector<std::function<void(sf::Event event)>> eventHandlers;
};


#endif