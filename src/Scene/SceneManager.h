#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <unordered_map>
#include <string>


namespace sge{
    class PhysicsManager;
    class CollisionManager;
    class TextureManager;
    class EntityManager;
    class DebugManager;
    class Scene;

    class SceneManager{
        public:
            SceneManager(
                sge::PhysicsManager* physicsManger,
                sge::CollisionManager* collisionManager,
                sge::TextureManager* textureManager,
                sge::EntityManager* entityManager,
                sge::DebugManager* debugManager
            );


            void registerScene(std::string name, sge::Scene* scene);
            void loadScene(std::string name);
        
        private:
            std::unordered_map<std::string, sge::Scene*> m_scenes;

            sge::PhysicsManager* m_physicsManager;
            sge::CollisionManager* m_collisionManagerPtr;
            sge::TextureManager* m_textureManager;
            sge::EntityManager* m_entityManagerPtr;
            sge::DebugManager* m_debugManager;
    };
}


#endif