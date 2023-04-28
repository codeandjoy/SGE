#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>


namespace sge{
    struct Collision;
    struct CollisionPair;
    class CollisionShape;

    class CollisionManager{
        public:
            void registerCollisionShape(sge::CollisionShape* collisionShape);
            void deregisterCollisionShape(sge::CollisionShape* collisionShape);
            void registerCollisionShapes(std::vector<sge::CollisionShape*> collisionShapes);
            void deregisterCollisionShapes(std::vector<sge::CollisionShape*> collisionShapes);
            void deregisterAllCollisionShapes();
            std::vector<sge::CollisionShape*> getAllCollisionShapes();
            void alignCollisionShapes();


            void registerCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionGroup);
            void deregisterCollisionGroup(std::string name);
            void registerCollisionGroups(std::unordered_map<std::string, std::vector<sge::CollisionShape*>> collisionGroups);
            void deregisterCollisionGroups(std::unordered_map<std::string, std::vector<sge::CollisionShape*>> collisionGroups);
            void deregisterAllCollisionGroups();
            std::unordered_map<std::string, std::vector<sge::CollisionShape*>> getCollisionGroups();


            void registerCollisionPair(std::string name, sge::CollisionPair* collisionPair);
            void registerCollisionPairs(std::unordered_map<std::string, CollisionPair*> collisionPairs);
            void setCollisionPairsOrder(std::vector<std::string> order);
            // ! remove
            void createCollisionPair(std::string name, std::string initiatorGroup, std::string recipientGroup);
            void setPairCollisionDetectionAlgorithm(std::string collisionPairName, std::function<bool(sge::CollisionShape*, sge::CollisionShape*)> collisionDetectionAlgorithm);
            void setPairCollisionResponse(std::string collisionPairName, std::string collisionPhase, std::function<void(std::vector<sge::Collision>)> response);
            // ! remove
            void deregisterCollisionPair(std::string name);
            void deregisterAllCollisionPairs();


            void updateCollisions();

        private:
            std::vector<sge::CollisionShape*> m_allCollisionShapes;
            std::unordered_map<std::string, std::vector<sge::CollisionShape*>> m_collisionGroups;
            std::unordered_map<std::string, sge::CollisionPair*> m_collisionPairs;
            std::vector<std::string> m_collisionPairsOrder;
    };
}


#endif