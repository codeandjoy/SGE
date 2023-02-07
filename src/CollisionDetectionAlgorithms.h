#ifndef COLLISION_DETECTION_ALGORITHMS_H
#define COLLISION_DETECTION_ALGORITHMS_H

#include "PhysicalObject.h"


bool boundingBox(PhysicalObject *PO1, PhysicalObject *PO2){
    printf("bb\n");
    return PO1->getGlobalBounds().intersects(PO2->getGlobalBounds());
}

// TODO
// bool rayRect(){}


#endif