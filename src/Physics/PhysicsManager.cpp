#include "PhysicsManager.h"

void PhysicsManager::registerPhysicalObject(PhysicalObject* physicalObject){ m_physicalObjects.push_back(physicalObject); }
void PhysicsManager::deregisterPhysicalObject(PhysicalObject* physicalObject){ m_physicalObjects.erase(std::remove(m_physicalObjects.begin(), m_physicalObjects.end(), physicalObject), m_physicalObjects.end()); }
std::vector<PhysicalObject*> PhysicsManager::getAllPhysicalObjects(){ return m_physicalObjects; }



void PhysicsManager::updatePhysics(float dt){
    for(PhysicalObject* physicalObject : m_physicalObjects){
        physicalObject->update(dt);
    }
}