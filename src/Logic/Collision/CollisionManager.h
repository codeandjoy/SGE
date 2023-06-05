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
    class CollisionShapeManager;

    class CollisionManager{
        public:
            CollisionManager(CollisionShapeManager* collisionShapeManager): m_collisionShapeManagerPtr(collisionShapeManager){};

            void registerCollisionPair(std::string name, sge::CollisionPair* collisionPair);
            void deregisterCollisionPair(std::string name);
            void registerCollisionPairs(std::unordered_map<std::string, CollisionPair*> collisionPairs);
            void setCollisionPairsOrder(std::vector<std::string> order);

            void updateCollisions();

        private:
            std::unordered_map<std::string, sge::CollisionPair*> m_collisionPairs;
            std::vector<std::string> m_collisionPairsOrder;

            CollisionShapeManager* m_collisionShapeManagerPtr;
    };
}


#endif