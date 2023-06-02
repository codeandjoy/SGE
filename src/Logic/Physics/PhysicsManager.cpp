#include "PhysicsManager.h"
#include "PhysicalObject.h"


void sge::PhysicsManager::update(float dt){
    for(sge::PhysicalObject* physicalObject : m_components){
        physicalObject->update(dt);
    }
}