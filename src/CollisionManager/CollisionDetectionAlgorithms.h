#ifndef COLLISION_DETECTION_ALGORITHMS_H
#define COLLISION_DETECTION_ALGORITHMS_H

#include "./CollisionShapes/CollisionShape.h"


bool boundingBox(CollisionShape *CS1, CollisionShape *CS2){
    return CS1->getGlobalBounds().intersects(CS2->getGlobalBounds());
}

// TODO
// bool rayRect(){}


#endif