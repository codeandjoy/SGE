#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include "../Physics/PhysicsManager.h"
#include "../Physics/PhysicalObject.h"
#include "../Collision/CollisionManager.h"
#include "../Texture/TextureManager.h"
#include "../Entity/EntityManager.h"
#include "../Debug/DebugManager.h"

class Universe{
    public:
        Universe(PhysicsManager* t_physicsManager, CollisionManager* t_collisionManager, TextureManager* t_textureManager, EntityManager* t_entityManager);
        Universe(PhysicsManager* t_physicsManager, CollisionManager* t_collisionManager, TextureManager* t_textureManager, EntityManager* t_entityManager, DebugManager* t_debugManager);


        void setupWindow(sf::RenderWindow* window);


        void addController(std::function<void()> controller);
        void addEventHandler(std::function<void(sf::Event event)> eventHandler);


        void loop();


        PhysicsManager* physicsManager;
        CollisionManager* collisionManager;
        TextureManager* textureManager;
        EntityManager* entityManager;
        DebugManager* debugManager;

    private:
        sf::RenderWindow* m_windowPtr;

        sf::Clock m_deltaClock;
        
        std::vector<std::function<void()>> m_controllers;
        std::vector<std::function<void(sf::Event event)>> m_eventHandlers;
};


#endif