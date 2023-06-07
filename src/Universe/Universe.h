#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>


namespace sge{
    class AssetsManager;
    class ControllerManager;
    class ScriptedViewManager;
    class DebugManager;

    class SpriteManager;
    class PhysicsManager;
    class CollisionShapeManager;
    class ClickableShapeManager;
    class SpriteTextManager;
    class AnimationManager;
    class StateManager;
    class CollisionManager;
    class EntityManager;
    class DrumSceneManager;
    class LayerSceneManager;
    

    class Universe{
        public:
            Universe(sf::RenderWindow* window);

            float dtCap = .15f;

            void setupDebug();
            void loop();


            sge::AssetsManager* assetsManager = nullptr;
            sge::ControllerManager* controllerManager = nullptr;
            sge::DebugManager* debugManager = nullptr;
            sge::ScriptedViewManager* scriptedViewManager = nullptr;

            sge::CollisionManager* collisionManager = nullptr;
            sge::EntityManager* entityManager = nullptr;
            sge::DrumSceneManager* drumSceneManager = nullptr;
            sge::LayerSceneManager* layerSceneManager = nullptr;

        private:
            sf::RenderWindow* m_windowPtr;

            sf::Clock m_deltaClock;


            sge::SpriteManager* m_spriteManager = nullptr;
            sge::PhysicsManager* m_physicsManager = nullptr;
            sge::CollisionShapeManager* m_collisionShapeManager = nullptr;
            sge::AnimationManager* m_animationManager = nullptr;
            sge::StateManager* m_stateManager = nullptr;

            sge::ClickableShapeManager* m_clickableShapeManager = nullptr;
            sge::SpriteTextManager* m_spriteTextManager = nullptr;
    };
}


#endif