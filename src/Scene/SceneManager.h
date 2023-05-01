#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <unordered_map>
#include <string>


namespace sge{
    class PhysicsManager;
    class CollisionManager;
    class AnimationManager;
    class EntityManager;
    class DebugManager;
    class Scene;

    class SceneManager{
        public:
            SceneManager(
                sge::PhysicsManager* physicsManger,
                sge::CollisionManager* collisionManager,
                sge::AnimationManager* animationManager,
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

            sge::PhysicsManager* m_physicsManagerPtr;
            sge::CollisionManager* m_collisionManagerPtr;
            sge::AnimationManager* m_animationManagerPtr;
            sge::EntityManager* m_entityManagerPtr;
            sge::DebugManager* m_debugManagerPtr;
    };
}


#endif