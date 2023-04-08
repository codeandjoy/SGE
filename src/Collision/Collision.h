#ifndef COLLISION_H
#define COLLISION_H

#include "CollisionSide.h"
#include "CollisionShape.h"


struct Collision{
    CollisionShape *initiator;
    CollisionShape *recipient;
    CollisionSide initiatorImpactSide;
    CollisionSide recipientImpactSide;
    // ? detectionAlgorithm (string?)
};


#endif