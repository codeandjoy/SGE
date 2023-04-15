#include "PhysicalObject.h"

std::function<void(float)> updatePositionBasedOnVelocity(PhysicalObject* physicalObject){
    return [physicalObject](float dt){
        physicalObject->setPosition(physicalObject->getPosition() + physicalObject->velocity * dt);
    };
}

std::function<void(float)> updateVelocityBasedOnAcceleration(PhysicalObject* physicalObject){
    return [physicalObject](float dt){
        if(abs(physicalObject->velocity.x) >= physicalObject->speedLimit.x){
            physicalObject->velocity.x = physicalObject->speedLimit.x;
        }
        else{
            physicalObject->velocity.x += physicalObject->acceleration.x;
        }

        if(abs(physicalObject->velocity.y) >= physicalObject->speedLimit.y){
            physicalObject->velocity.y = physicalObject->speedLimit.y;
        }
        else{
            physicalObject->velocity.y += physicalObject->acceleration.y;
        }
    };
}