#include "PhysicsManager.h"

void PhysicsManager::registerPhysicalObject(PhysicalObject* _physicalObject){ physicalObjects.push_back(_physicalObject); }

void PhysicsManager::deregisterPhysicalObject(PhysicalObject* _physicalObject){ physicalObjects.erase(std::remove(physicalObjects.begin(), physicalObjects.end(), _physicalObject), physicalObjects.end()); }

std::vector<PhysicalObject*> PhysicsManager::getAllPhysicalObjects(){ return physicalObjects; }

void PhysicsManager::updatePhysics(float dt){
    // TODO check if any physical objects exist
    for(PhysicalObject* physicalObject : physicalObjects){
        // Gravity
        if(!physicalObject->getIsFlying()){
            physicalObject->setVelocityGoalY(physicalObject->getMass());
        }

        physicalObject->update(dt);
    }
}