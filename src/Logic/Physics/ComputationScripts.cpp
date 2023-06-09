#include "ComputationScripts.h"
#include "PhysicalObject.h"



std::function<void(sge::PhysicalObject*, float)> sge::updatePositionBasedOnVelocity(){
    return [](sge::PhysicalObject* thisPhysicalObject, float dt){
        thisPhysicalObject->getOwnerSprite()->setPosition(thisPhysicalObject->getOwnerSprite()->getPosition() + thisPhysicalObject->velocity * dt);
    };
}

std::function<void(sge::PhysicalObject*, float)> sge::updateVelocityBasedOnAcceleration(sf::Vector2f speedLimit){
    return [speedLimit](sge::PhysicalObject* thisPhysicalObject, float dt){
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