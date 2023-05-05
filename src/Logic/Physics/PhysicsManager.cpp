#include "PhysicsManager.h"
#include "PhysicalObject.h"


void sge::PhysicsManager::registerPhysicalObject(sge::PhysicalObject* physicalObject){ m_physicalObjects.push_back(physicalObject); }
void sge::PhysicsManager::deregisterPhysicalObject(sge::PhysicalObject* physicalObject){ m_physicalObjects.erase(std::remove(m_physicalObjects.begin(), m_physicalObjects.end(), physicalObject), m_physicalObjects.end()); }
void sge::PhysicsManager::deregisterAllPhysicalObjects(){ m_physicalObjects.clear(); }
std::vector<sge::PhysicalObject*> sge::PhysicsManager::getAllPhysicalObjects(){ return m_physicalObjects; }



void sge::PhysicsManager::updatePhysics(float dt){
    for(sge::PhysicalObject* physicalObject : m_physicalObjects){
        physicalObject->update(dt);
    }
}