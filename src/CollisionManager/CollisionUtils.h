#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

#include <limits>
#include "./CollisionShapes/CollisionShape.h"
#include "CollisionSide.h"


float determineCollisionDepth(CollisionSide side, CollisionShape *CS1, CollisionShape *CS2){
    auto [x1, y1, height1, width1] = CS1->getPositionData();
    auto [x2, y2, height2, width2] = CS2->getPositionData();
    
    if(side == CollisionSide::left) return x2 + width2 - x1;
    if(side == CollisionSide::right) return x1 + width1 - x2;
    if(side == CollisionSide::top) return y2 + height2 - y1;
    if(side == CollisionSide::bottom) return y1 + height1 - y2;

    return 0;
}

CollisionSide determineCollisionSide(CollisionShape *CS1, CollisionShape *CS2){
    std::vector<CollisionSide> allCollisionSides;

    // ! Order matters 
    if(CS1->getOwner()->getMovementVector().x < 0) allCollisionSides.push_back(CollisionSide::left);
    if(CS1->getOwner()->getMovementVector().x > 0) allCollisionSides.push_back(CollisionSide::right);
    if(CS1->getOwner()->getMovementVector().y < 0) allCollisionSides.push_back(CollisionSide::top);
    if(CS1->getOwner()->getMovementVector().y > 0) allCollisionSides.push_back(CollisionSide::bottom);


    CollisionSide lowestDepthSide;
    float lowestDepth = std::numeric_limits<float>::infinity();
    
    for(CollisionSide collisionSide : allCollisionSides){
        float depth = determineCollisionDepth(collisionSide, CS1, CS2);
        if(depth <= lowestDepth){
            lowestDepthSide = collisionSide;
            lowestDepth = depth;
        }
    }

    return lowestDepthSide;
}


#endif