#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>


namespace sge{
    class AssetsManager;
    class ControllerManager;

    class ScriptedViewManager;
    class SpriteManager;
    class PhysicsManager;
    class PhysicalObject;
    class CollisionShapeManager;
    class AnimationManager;
    class CollisionManager;
    class EntityManager;
    class DebugManager;
    class SceneManager;
    
    class UISpriteManager;
    class ClickableShapeManager;
    class SpriteTextManager;
    class UIAnimationManager;
    class UIEntityManager;

    class Universe{
        public:
            Universe();

            bool isPaused = false;

            void setupWindow(sf::RenderWindow* window);
            void loop();


            sge::AssetsManager* assetsManager = nullptr;
            sge::ControllerManager* controllerManager = nullptr;

            sge::ScriptedViewManager* scriptedViewManager = nullptr;
            sge::SpriteManager* spriteManager = nullptr;
            sge::PhysicsManager* physicsManager = nullptr;
            sge::CollisionShapeManager* collisionShapeManager = nullptr;
            sge::AnimationManager* animationManager = nullptr;
            sge::CollisionManager* collisionManager = nullptr;
            sge::EntityManager* entityManager = nullptr;
            sge::DebugManager* debugManager = nullptr;
            sge::SceneManager* sceneManager = nullptr;

            sge::UISpriteManager* uiSpriteManager = nullptr;
            sge::ClickableShapeManager* clickableShapeManager = nullptr;
            sge::SpriteTextManager* spriteTextManager = nullptr;
            sge::UIAnimationManager* uiAnimationManager = nullptr;
            sge::UIEntityManager* uiEntityManager = nullptr;

        private:
            sf::RenderWindow* m_windowPtr;
            sf::View m_uiView;

            sf::Clock m_deltaClock;
    };
}


#endif