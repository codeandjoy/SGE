#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>


namespace sge{
    class SpriteManager;
    class PhysicsManager;
    class PhysicalObject;
    class CollisionManager;
    class TextureManager;
    class EntityManager;
    class DebugManager;
    class SceneManager;
    
    class Universe{
        public:
            Universe();


            bool isPaused = false;


            void setupWindow(sf::RenderWindow* window);


            void addController(std::function<void()> controller);
            void addEventHandler(std::function<void(sf::Event event)> eventHandler);


            void loop();


            sge::SpriteManager* spriteManager = nullptr;
            sge::PhysicsManager* physicsManager = nullptr;
            sge::CollisionManager* collisionManager = nullptr;
            sge::TextureManager* textureManager = nullptr;
            sge::EntityManager* entityManager = nullptr;
            sge::DebugManager* debugManager = nullptr;
            sge::SceneManager* sceneManager = nullptr;

        private:
            sf::RenderWindow* m_windowPtr;

            sf::Clock m_deltaClock;
            
            std::vector<std::function<void()>> m_controllers;
            std::vector<std::function<void(sf::Event event)>> m_eventHandlers;
    };
}


#endif