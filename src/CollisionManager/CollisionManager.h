#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <SFML/Graphics.hpp>
#include "../PhysicsManager/PhysicalObject.h"
#include "CollisionGroup.h"
#include "CollisionGroupType.h"
#include "CollisionPair.h"
#include "Collision.h"
#include "./CollisionShapes/CollisionShape.h"


// ? allow to add an 'area' where collisions get calculated 
// ? addToGroup(...), removeFromGroup(...), reloadGroup(...) (checks if pointers are still valid), removePair(...), removeCOllisionResponse(...)
class CollisionManager{
    public:
    void createCollisionGroup(std::string name, CollisionGroupType type, std::vector<CollisionShape*> collisionShapes);
    void createCollisionPair(std::string name, std::string group1, std::string group2);
    void addCollisionResponse(std::string collisionPairName, const std::function<void(std::vector<Collision>)> &response);
    void setCollisionDetectionAlgorithm(std::string collisionPairName, const std::function<bool(CollisionShape *CS1, CollisionShape *CS2)> &cda);

    std::map<std::string, CollisionGroup> getCollisionGroups();

    void updateCollisions();

    private:
    std::map<std::string, CollisionGroup> collisionGroups;
    std::map<std::string, CollisionPair> collisionPairs;
};


#endif