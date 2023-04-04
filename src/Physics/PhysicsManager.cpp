#include "PhysicsManager.h"

void PhysicsManager::registerPhysicalObject(PhysicalObject* _physicalObject){ physicalObjects.push_back(_physicalObject); }

void PhysicsManager::deregisterPhysicalObject(PhysicalObject* _physicalObject){ physicalObjects.erase(std::remove(physicalObjects.begin(), physicalObjects.end(), _physicalObject), physicalObjects.end()); }

std::vector<PhysicalObject*> PhysicsManager::getAllPhysicalObjects(){ return physicalObjects; }

void PhysicsManager::updatePhysics(float dt){
    for(PhysicalObject* physicalObject : physicalObjects){
        // Accelerate (approach with step)
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
        //

        physicalObject->update(dt);
    }
}