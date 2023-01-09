#include "PhysicsManager.h"

void PhysicsManager::addPhysicalObject(PhysicalObject *physicalObject){
    physicalObjects.push_back(physicalObject);
}

void PhysicsManager::addSolidObject(SolidObject *solidObject){
    solidObjects.push_back(solidObject);
}

std::vector<SolidObject*>* PhysicsManager::getSolidObjects(){
    return &solidObjects;
}

void PhysicsManager::updatePhysics(){
    // TODO check if any physical objects exist
    for(PhysicalObject *pObject : physicalObjects){
        pObject->updatePhysics();
    }
    // TODO check if any solid objects exist
    for(SolidObject *sObject : solidObjects){
        sObject->updateSolidObject();
    }
}