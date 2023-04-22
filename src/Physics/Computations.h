#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

class PhysicalObject;


std::function<void(float)> updatePositionBasedOnVelocity(PhysicalObject* physicalObject);

std::function<void(float)> updateVelocityBasedOnAcceleration(PhysicalObject* physicalObject);


#endif