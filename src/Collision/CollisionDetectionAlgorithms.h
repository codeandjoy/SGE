#ifndef COLLISION_DETECTION_ALGORITHMS_H
#define COLLISION_DETECTION_ALGORITHMS_H

#include "CollisionShape.h"


bool boundingBox(CollisionShape *initiator, CollisionShape *recipient){
    return initiator->getGlobalBounds().intersects(recipient->getGlobalBounds());
}

// TODO
// bool rayRect(){}


#endif