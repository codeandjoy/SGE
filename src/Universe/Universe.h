#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>


namespace sge{
    class AssetsManager;
    class ControllerManager;
    class ScriptedViewManager;
    class DebugEntityManager;
    class DebugScreenManager;

    class SpriteManager;
    class MotionUnitManager;
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

            void setupDebugEntityManager();
            void setupDebugScreenManager(sf::View* debugScreenView, sf::Font* debugScreenFont, int fontSize);
            void loop();


            sge::AssetsManager* assetsManager = nullptr;
            sge::ControllerManager* controllerManager = nullptr;
            sge::ScriptedViewManager* scriptedViewManager = nullptr;
            sge::DebugEntityManager* debugEntityManager = nullptr;
            sge::DebugScreenManager* debugScreenManager = nullptr;

            sge::CollisionManager* collisionManager = nullptr;
            sge::EntityManager* entityManager = nullptr;
            sge::DrumSceneManager* drumSceneManager = nullptr;
            sge::LayerSceneManager* layerSceneManager = nullptr;

        private:
            sf::RenderWindow* m_windowPtr;

            sf::Clock m_deltaClock;


            sge::SpriteManager* m_spriteManager = nullptr;
            sge::MotionUnitManager* m_motionUnitManager = nullptr;
            sge::CollisionShapeManager* m_collisionShapeManager = nullptr;
            sge::AnimationManager* m_animationManager = nullptr;
            sge::StateManager* m_stateManager = nullptr;

            sge::ClickableShapeManager* m_clickableShapeManager = nullptr;
            sge::SpriteTextManager* m_spriteTextManager = nullptr;
    };
}


#endif