#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <SFML/Graphics.hpp>
#include "CollisionPair.h"
#include "CollisionShape.h"


// ? addToGroup(...), removeFromGroup(...), reloadGroup(...) (checks if pointers are still valid), removePair(...), removeCOllisionResponse(...)
class CollisionManager{
    public:
        void registerCollisionShape(CollisionShape* collisionShape);
        void deregisterCollisionShape(CollisionShape* collisionShape);
        void registerCollisionShapes(std::vector<CollisionShape*> collisionShapes);
        void degisterCollisionShapes(std::vector<CollisionShape*> collisionShapes);
        std::vector<CollisionShape*> getAllCollisionShapes();
        void alignCollisionShapes();


        void registerCollisionGroup(std::string name, std::vector<CollisionShape*> collisionGroup);
        void deregisterCollisionGroup(std::string name);
        void registerCollisionGroups(std::unordered_map<std::string, std::vector<CollisionShape*>> collisionGroups);
        void deregisterCollisionGroups(std::unordered_map<std::string, std::vector<CollisionShape*>> collisionGroups);
        std::unordered_map<std::string, std::vector<CollisionShape*>> getCollisionGroups();


        void createCollisionPair(std::string name, std::string initiatorGroup, std::string recipientGroup);
        void setPairCollisionDetectionAlgorithm(std::string collisionPairName, std::function<bool(CollisionShape* initiator, CollisionShape* recipient)> collisionDetectionAlgorithm);
        void setPairCollisionResponse(std::string collisionPairName, std::string collisionPhase, std::function<void(std::vector<Collision>)> response);


        void updateCollisions();

    private:
        std::vector<CollisionShape*> m_allCollisionShapes;
        std::unordered_map<std::string, std::vector<CollisionShape*>> m_collisionGroups;
        std::unordered_map<std::string, CollisionPair> m_collisionPairs;
};


#endif