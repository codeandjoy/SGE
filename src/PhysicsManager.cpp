#include "PhysicsManager.h"

void PhysicsManager::addPhysicalObject(PhysicalObject *physicalObject){
    physicalObjects.push_back(physicalObject);
}

void PhysicsManager::updatePhysics(float dt){
    // TODO check if any physical objects exist
    for(PhysicalObject *pObject : physicalObjects){
        // * Gravity
        if(!pObject->getIsFlying()){
            pObject->setMovementVectorY(pObject->getMass());
        }
        // *

        pObject->update(dt);
    }
}