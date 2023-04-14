#include "PhysicsManager.h"

void PhysicsManager::registerPhysicalObject(PhysicalObject* physicalObject){ m_physicalObjects.push_back(physicalObject); }
void PhysicsManager::deregisterPhysicalObject(PhysicalObject* physicalObject){ m_physicalObjects.erase(std::remove(m_physicalObjects.begin(), m_physicalObjects.end(), physicalObject), m_physicalObjects.end()); }
std::vector<PhysicalObject*> PhysicsManager::getAllPhysicalObjects(){ return m_physicalObjects; }



void PhysicsManager::updatePhysics(float dt){
    for(PhysicalObject* physicalObject : m_physicalObjects){
        // !
        // !
        // !
        // ? Should be in physicalObject.update ?
        // ? Is it just the continuous action ?
        // !
        // !
        // !
        // Accelerate (approach speed limit with acceleration step)
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