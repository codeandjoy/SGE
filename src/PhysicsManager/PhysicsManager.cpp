#include "PhysicsManager.h"

void PhysicsManager::addPhysicalObject(std::string _name, PhysicalObject* _physicalObject){ physicalObjects[_name] = _physicalObject; }

void PhysicsManager::removePhysicalObject(std::string _name){ physicalObjects.erase(_name); }

void PhysicsManager::updatePhysics(float dt){
    // TODO check if any physical objects exist
    for(auto& [key, physicalObject] : physicalObjects){
        // Gravity
        if(!physicalObject->getIsFlying()){
            physicalObject->setVelocityGoalY(physicalObject->getMass());
        }

        physicalObject->update(dt);
    }
}