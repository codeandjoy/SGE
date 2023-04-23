#include "Computations.h"
#include "PhysicalObject.h"



std::function<void(PhysicalObject*, float)> updatePositionBasedOnVelocity(){
    return [](PhysicalObject* thisPhysicalObject, float dt){
        thisPhysicalObject->setPosition(thisPhysicalObject->getPosition() + thisPhysicalObject->velocity * dt);
    };
}

std::function<void(PhysicalObject*, float)> updateVelocityBasedOnAcceleration(sf::Vector2f speedLimit){
    return [speedLimit](PhysicalObject* thisPhysicalObject, float dt){
        if(abs(thisPhysicalObject->velocity.x) >= speedLimit.x){
            thisPhysicalObject->velocity.x = speedLimit.x;
        }
        else{
            thisPhysicalObject->velocity.x += thisPhysicalObject->acceleration.x;
        }

        if(abs(thisPhysicalObject->velocity.y) >= speedLimit.y){
            thisPhysicalObject->velocity.y = speedLimit.y;
        }
        else{
            thisPhysicalObject->velocity.y += thisPhysicalObject->acceleration.y;
        }
    };
}