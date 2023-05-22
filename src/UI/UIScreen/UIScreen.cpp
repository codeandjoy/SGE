#include <algorithm>

#include "UIScreen.h"
#include "../UIEntity/UIEntityManager.h"


void sge::UIScreen::addUIEntity(sge::UIEntity* uiEntity){ m_uiEntities.push_back(uiEntity); }
void sge::UIScreen::removeUIEntity(sge::UIEntity* uiEntity){ m_uiEntities.erase(std::remove(m_uiEntities.begin(), m_uiEntities.end(), uiEntity), m_uiEntities.end()); }
std::vector<sge::UIEntity*> sge::UIScreen::getUIEntities(){ return m_uiEntities; }