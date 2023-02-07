#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "SFML/Graphics.hpp"
#include "PhysicalObject.h"
#include "CollisionGroup.h"
#include "CollisionGroupType.h"
#include "CollisionPair.h"


// ? allow to add an 'area' where collisions get calculated 
// ? addToGroup(...), removeFromGroup(...), reloadGroup(...) (checks if pointers are still valid), removePair(...), removeCOllisionResponse(...)
class CollisionManager{
    public:
    void createCollisionGroup(std::string name, CollisionGroupType type, std::vector<PhysicalObject*> physicalObjectsVec); // TODO Overload 3rd argument with sf::Sprite *sprite (and automatically create a vector)
    void createCollisionPair(std::string name, std::string group1, std::string group2);
    void addCollisionResponse(std::string collisionPairName, const std::function<void(PhysicalObject *physicalObject1, PhysicalObject *physicalObject2)> &response);
    void setCollisionDetectionAlgorithm(std::string collisionPairName, const std::function<bool(PhysicalObject *PO1, PhysicalObject *PO2)> &cda);

    void updateCollisions();

    private:
    std::map<std::string, CollisionGroup> collisionGroups;
    std::map<std::string, CollisionPair> collisionPairs;
};


#endif