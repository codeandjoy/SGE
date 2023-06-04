#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <unordered_map>
#include <string>

#include "../../Manager/StorageManagers/LabelManager.h"


namespace sge{
    class Scene;
    class EntityManager;
    class CollisionManager;
    class DebugManager;

    class SceneManager : public sge::LabelManager<sge::Scene*>{
        public:
            SceneManager(sge::EntityManager* entityManager, sge::CollisionManager* collisionManager);
            void setupDebug(sge::DebugManager* debugManager);
        
        protected:
            void m_registerSceneMembers(std::string label);
            void m_deregisterSceneMembers(std::string label);

            sge::EntityManager* m_entityManagerPtr = nullptr;
            sge::CollisionManager* m_collisionManagerPtr = nullptr;
            sge::DebugManager* m_debugManagerPtr = nullptr;
    };
}


#endif