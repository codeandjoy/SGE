#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <SFML/Graphics.hpp>
#include "CollisionPair.h"
#include "CollisionShape.h"


// ? allow to add an 'area' where collisions get calculated 
// ? addToGroup(...), removeFromGroup(...), reloadGroup(...) (checks if pointers are still valid), removePair(...), removeCOllisionResponse(...)
class CollisionManager{
    public:
        void registerCollisionShape(CollisionShape* _collisionShape);
        void deregisterCollisionShape(CollisionShape* _collisionShape);
        void registerCollisionShapes(std::vector<CollisionShape*> _collisionShapes);
        void degisterCollisionShapes(std::vector<CollisionShape*> _collisionShapes);

        void registerCollisionGroup(std::string name, std::vector<CollisionShape*> _collisionGroup);
        void deregisterCollisionGroup(std::string name);
        void registerCollisionGroups(std::map<std::string, std::vector<CollisionShape*>> _groupsToRegister);
        void deregisterCollisionGroups(std::map<std::string, std::vector<CollisionShape*>> _groupsToDeregister);
        
        void createCollisionPair(std::string name, std::string group1, std::string group2);
        void setCollisionResponse(std::string collisionPairName, std::string collisionPhase, std::function<void(std::vector<Collision>)> response);
        void setCollisionDetectionAlgorithm(std::string collisionPairName, std::function<bool(CollisionShape* initiator, CollisionShape* recipient)> cda);

        std::vector<CollisionShape*> getAllCollisionShapes();
        std::map<std::string, std::vector<CollisionShape*>> getCollisionGroups();

        void alignCollisionShapes();
        void updateCollisions();

    private:
        std::vector<CollisionShape*> allCollisionShapes;
        std::map<std::string, std::vector<CollisionShape*>> collisionGroups;
        std::map<std::string, CollisionPair> collisionPairs;
};


#endif