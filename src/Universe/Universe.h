#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
class PhysicsManager;
class PhysicalObject;
class CollisionManager;
class TextureManager;
class EntityManager;
class DebugManager;


class Universe{
    public:
        Universe(bool DEBUG = false);


        void setupWindow(sf::RenderWindow* window);


        void addController(std::function<void()> controller);
        void addEventHandler(std::function<void(sf::Event event)> eventHandler);


        void loop();


        PhysicsManager* physicsManager = nullptr;
        CollisionManager* collisionManager = nullptr;
        TextureManager* textureManager = nullptr;
        EntityManager* entityManager = nullptr;
        DebugManager* debugManager = nullptr;

    private:
        sf::RenderWindow* m_windowPtr;

        sf::Clock m_deltaClock;
        
        std::vector<std::function<void()>> m_controllers;
        std::vector<std::function<void(sf::Event event)>> m_eventHandlers;
};


#endif