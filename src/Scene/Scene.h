#ifndef SCENE_H
#define SCENE_H

#include <unordered_map>
#include <vector>
#include <string>


namespace sge{
    class Entity;
    class DebugEntity;
    class CollisionShape;
    struct CollisionPair;

    class Scene{
        public:
            void registerEntity(sge::Entity* entity);
            void registerEntities(std::vector<sge::Entity*> entities);
            void registerDebugEntity(sge::DebugEntity* debugEntity);
            void registerDebugEntities(std::vector<sge::DebugEntity*> debugEntities);
            void registerCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionShapes);
            void registerCollisionPair(std::string name, sge::CollisionPair* collisionPair);
        
        
            std::vector<sge::Entity*> getEntities();
            std::vector<sge::DebugEntity*> getDebugEntities();
            std::unordered_map<std::string, std::vector<sge::CollisionShape*>> getCollisionGroups();
            std::unordered_map<std::string, sge::CollisionPair*> getCollisionPairs();
            std::vector<std::string> getCollisionPairsOrder();

        private:
            std::vector<sge::Entity*> m_entities;
            std::vector<sge::DebugEntity*> m_debugEntities;
            std::unordered_map<std::string, std::vector<sge::CollisionShape*>> m_collisionGroups;
            std::unordered_map<std::string, sge::CollisionPair*> m_collisionPairs;
            std::vector<std::string> m_collisionPairsOrder;
    };
}


#endif