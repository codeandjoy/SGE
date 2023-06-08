#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <unordered_map>
#include <string>

#include "../../Manager/StorageManagers/LabelManager.h"


namespace sge{
    class Scene;
    class EntityManager;
    class CollisionManager;
    class DebugEntityManager;

    class SceneManager : public sge::LabelManager<sge::Scene*>{
        public:
            SceneManager(sge::EntityManager* entityManager): m_entityManagerPtr(entityManager){};
            void setupDebug(sge::DebugEntityManager* debugEntityManager);
        
        protected:
            void m_registerSceneMembers(std::string label);
            void m_deregisterSceneMembers(std::string label);

            sge::EntityManager* m_entityManagerPtr = nullptr;
            sge::DebugEntityManager* m_debugEntityManagerPtr = nullptr;
    };
}


#endif