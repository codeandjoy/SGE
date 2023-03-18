#ifndef COLLISION_H
#define COLLISION_H

#include "../PhysicsManager/PhysicalObject.h"
#include "CollisionSide.h"


struct Collision{
    CollisionSide side;
    PhysicalObject *from;
    PhysicalObject *with;
    // ? detectionAlgorithm (string?)
};


#endif