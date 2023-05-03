#include <algorithm>
#include "ClickableShapeManager.h"
#include "ClickableShape.h"


void sge::ClickableShapeManager::registerClickableShape(sge::ClickableShape* clickableShape){ m_activeClickableShapes.push_back(clickableShape); }
void sge::ClickableShapeManager::deregsiterClickableShape(sge::ClickableShape* clickableShape){
    m_activeClickableShapes.erase(std::remove(m_activeClickableShapes.begin(), m_activeClickableShapes.end(), clickableShape), m_activeClickableShapes.end());
    m_inactiveClickableShapes.erase(std::remove(m_inactiveClickableShapes.begin(), m_inactiveClickableShapes.end(), clickableShape), m_inactiveClickableShapes.end());
}



void sge::ClickableShapeManager::activateClickableShape(sge::ClickableShape* clickableShape){
    deregsiterClickableShape(clickableShape);
    m_activeClickableShapes.push_back(clickableShape);
}
void sge::ClickableShapeManager::deactivateClickableShape(sge::ClickableShape* clickableShape){
    deregsiterClickableShape(clickableShape);
    m_inactiveClickableShapes.push_back(clickableShape);
}



void sge::ClickableShapeManager::alignClickableShapes(){
    for(sge::ClickableShape* clickableShape : m_activeClickableShapes){
        clickableShape->align();
    }
}