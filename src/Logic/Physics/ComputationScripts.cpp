#include "ComputationScripts.h"
#include "MotionUnit.h"



std::function<void(sge::MotionUnit*, float)> sge::updatePositionBasedOnVelocity(){
    return [](sge::MotionUnit* thisPhysicalObject, float dt){
        thisPhysicalObject->getOwnerSprite()->setPosition(thisPhysicalObject->getOwnerSprite()->getPosition() + thisPhysicalObject->velocity * dt);
    };
}

std::function<void(sge::MotionUnit*, float)> sge::updateVelocityBasedOnAcceleration(sf::Vector2f speedLimit){
    return [speedLimit](sge::MotionUnit* thisPhysicalObject, float dt){
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