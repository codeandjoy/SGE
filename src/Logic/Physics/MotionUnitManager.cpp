#include "MotionUnitManager.h"
#include "MotionUnit.h"


void sge::MotionUnitManager::update(float dt){
    for(sge::MotionUnit* motionUnit : m_components){
        if(motionUnit->isActive) motionUnit->update(dt);
    }
}