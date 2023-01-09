#include "PhysicsManager.h"

void PhysicsManager::addPhysicalObject(PhysicalObject *physicalObject){
    physicalObjects.push_back(physicalObject);
}

void PhysicsManager::updatePhysics(){
    // TODO check if any physical objects exist
    for(PhysicalObject *pObject : physicalObjects){
        pObject->updatePhysics();
    }
}