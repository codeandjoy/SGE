#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <SFML/Graphics.hpp>
#include "../Physics/PhysicalObject.h"
#include "CollisionGroup.h"
#include "CollisionGroupType.h"
#include "CollisionPair.h"
#include "Collision.h"
#include "CollisionShape.h"


// ? allow to add an 'area' where collisions get calculated 
// ? addToGroup(...), removeFromGroup(...), reloadGroup(...) (checks if pointers are still valid), removePair(...), removeCOllisionResponse(...)
class CollisionManager{
    public:
        void registerCollisionGroup(std::string name, CollisionGroup* _collisionGroup);
        void deregisterCollisionGroup(std::string name);
        void registerCollisionGroups(std::map<std::string, CollisionGroup*> _groupsToRegister);
        void deregisterCollisionGroups(std::map<std::string, CollisionGroup*> _groupsToDeregister);
        
        void createCollisionPair(std::string name, std::string group1, std::string group2);
        void addCollisionResponse(std::string collisionPairName, const std::function<void(std::vector<Collision>)> &response);
        void setCollisionDetectionAlgorithm(std::string collisionPairName, const std::function<bool(CollisionShape *CS1, CollisionShape *CS2)> &cda);

        std::map<std::string, CollisionGroup*> getCollisionGroups();

        void updateCollisions();

    private:
        std::map<std::string, CollisionGroup*> collisionGroups;
        std::map<std::string, CollisionPair> collisionPairs;
};


#endif