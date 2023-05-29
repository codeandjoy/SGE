#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <unordered_map>
#include <string>


namespace sge{
    class Scene;
    class EntityManager;
    class CollisionManager;
    class DebugManager;

    class SceneManager{
        public:
            SceneManager(sge::EntityManager* entityManager, sge::CollisionManager* collisionManager);

            void setupDebug(sge::DebugManager* debugManager);

            void registerScene(std::string name, sge::Scene* scene);
            void setCurrentScene(std::string name);
            void alignScene();
        
        private:
            std::unordered_map<std::string, sge::Scene*> m_scenes;
            std::string m_currentScene = "";
            std::string m_loadedScene = "";

            sge::EntityManager* m_entityManagerPtr = nullptr;
            sge::CollisionManager* m_collisionManagerPtr = nullptr;
            sge::DebugManager* m_debugManagerPtr = nullptr;
    };
}


#endif