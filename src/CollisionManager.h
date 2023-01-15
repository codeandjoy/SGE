#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "CollisionGroup.h"
#include "CollisionPair.h"
#include "CollisionGroupType.h"


// ? allow to add an 'area' where collisions get calculated 
// ? addToGroup(...), removeFromGroup(...), reloadGroup(...) (checks if pointers are still valid), removePair(...)
class CollisionManager{
    public:
    void createCollisionGroup(std::string name, CollisionGroupType type, std::vector<sf::Sprite*> spriteVec); // TODO Overload 3rd argument with sf::Sprite *sprite (and automatically create a vector)
    void createCollisionPair(std::string name, std::string group1, std::string group2);
    void addCollisionResponse(std::string collisionPairName, const std::function<void()> &response);

    void updateCollisions();

    private:
    std::map<std::string, CollisionGroup> collisionGroups;
    std::map<std::string, CollisionPair> collisionPairs;
};


#endif