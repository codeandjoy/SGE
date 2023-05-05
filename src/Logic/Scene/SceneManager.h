#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <unordered_map>
#include <string>


namespace sge{
    class SpriteManager;
    class PhysicsManager;
    class CollisionShapeManager;
    class AnimationManager;
    class CollisionManager;
    class EntityManager;
    class DebugManager;
    class Scene;

    class SceneManager{
        public:
            SceneManager(
                sge::SpriteManager* spriteManager,
                sge::PhysicsManager* physicsManager,
                sge::CollisionShapeManager* collisionShapeManager,
                sge::AnimationManager* animationManager,
                sge::CollisionManager* collisionManager,
                sge::EntityManager* entityManager,
                sge::DebugManager* debugManager
            );


            void registerScene(std::string name, sge::Scene* scene);
            void setCurrentScene(std::string name);
            void alignScene();
        
        private:
            std::unordered_map<std::string, sge::Scene*> m_scenes;
            std::string m_currentScene = "";
            std::string m_loadedScene = "";

            sge::SpriteManager* m_spriteManagerPtr;
            sge::PhysicsManager* m_physicsManagerPtr;
            sge::CollisionShapeManager* m_collisionShapeManagerPtr;
            sge::AnimationManager* m_animationManagerPtr;
            sge::CollisionManager* m_collisionManagerPtr;
            sge::EntityManager* m_entityManagerPtr;
            sge::DebugManager* m_debugManagerPtr;
    };
}


#endif