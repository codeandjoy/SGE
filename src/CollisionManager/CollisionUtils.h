#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

#include <limits>
#include "../PhysicsManager/PhysicalObject.h"
#include "CollisionSide.h"


float determineCollisionDepth(CollisionSide side, PhysicalObject *PO1, PhysicalObject *PO2){
    auto [x1, y1, height1, width1] = PO1->getPositionData();
    auto [x2, y2, height2, width2] = PO2->getPositionData();
    
    if(side == CollisionSide::left) return x2 + width2 - x1;
    if(side == CollisionSide::right) return x1 + width1 - x2;
    if(side == CollisionSide::top) return y2 + height2 - y1;
    if(side == CollisionSide::bottom) return y1 + height1 - y2;

    return 0;
}

CollisionSide determineCollisionSide(PhysicalObject *PO1, PhysicalObject *PO2){
    std::vector<CollisionSide> allCollisionSides;

    // ! Order matters 
    if(PO1->getMovementVector().x < 0) allCollisionSides.push_back(CollisionSide::left);
    if(PO1->getMovementVector().x > 0) allCollisionSides.push_back(CollisionSide::right);
    if(PO1->getMovementVector().y < 0) allCollisionSides.push_back(CollisionSide::top);
    if(PO1->getMovementVector().y > 0) allCollisionSides.push_back(CollisionSide::bottom);


    CollisionSide lowestDepthSide;
    float lowestDepth = std::numeric_limits<float>::infinity();
    
    for(CollisionSide collisionSide : allCollisionSides){
        float depth = determineCollisionDepth(collisionSide, PO1, PO2);
        if(depth <= lowestDepth){
            lowestDepthSide = collisionSide;
            lowestDepth = depth;
        }
    }

    return lowestDepthSide;
}


#endif