#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

#include <limits>
#include "CollisionShape.h"
#include "CollisionSide.h"


float determineCollisionDepth(CollisionSide initiatorImpactSide, CollisionShape *initiator, CollisionShape *recipient){
    auto [x1, y1, height1, width1] = initiator->getMeasurements();
    auto [x2, y2, height2, width2] = recipient->getMeasurements();
    
    if(initiatorImpactSide == CollisionSide::left) return x2 + width2 - x1;
    if(initiatorImpactSide == CollisionSide::right) return x1 + width1 - x2;
    if(initiatorImpactSide == CollisionSide::top) return y2 + height2 - y1;
    if(initiatorImpactSide == CollisionSide::bottom) return y1 + height1 - y2;

    return 0;
}

CollisionSide determineInitiatorImpactSide(CollisionShape *initiator, CollisionShape *recipient){
    std::vector<CollisionSide> allImpactSides;

    // ! Order matters 
    if(initiator->getOwner()->velocity.x < 0) allImpactSides.push_back(CollisionSide::left);
    if(initiator->getOwner()->velocity.x > 0) allImpactSides.push_back(CollisionSide::right);
    if(initiator->getOwner()->velocity.y < 0) allImpactSides.push_back(CollisionSide::top);
    if(initiator->getOwner()->velocity.y > 0) allImpactSides.push_back(CollisionSide::bottom);


    CollisionSide lowestDepthSide;
    float lowestDepth = std::numeric_limits<float>::infinity();
    
    for(CollisionSide collisionSide : allImpactSides){
        float depth = determineCollisionDepth(collisionSide, initiator, recipient);
        if(depth <= lowestDepth){
            lowestDepthSide = collisionSide;
            lowestDepth = depth;
        }
    }

    return lowestDepthSide;
}

CollisionSide flipInitiatorImpactSide(CollisionSide initiatorImpactSide){
    if(initiatorImpactSide == CollisionSide::top) return CollisionSide::bottom;
    if(initiatorImpactSide == CollisionSide::bottom) return CollisionSide::top;
    if(initiatorImpactSide == CollisionSide::right) return CollisionSide::left;
    if(initiatorImpactSide == CollisionSide::left) return CollisionSide::right;

    return CollisionSide::bottom;
}


#endif