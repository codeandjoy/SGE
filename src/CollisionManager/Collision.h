#ifndef COLLISION_H
#define COLLISION_H

#include "CollisionSide.h"
#include "./CollisionShapes/CollisionShape.h"


struct Collision{
    CollisionSide side;
    CollisionShape *from;
    CollisionShape *with;
    // ? detectionAlgorithm (string?)
};


#endif