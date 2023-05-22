#include "UIScreenManager.h"
#include "../UIEntity/UIEntityManager.h"
#include "UIScreen.h"


sge::UIScreenManager::UIScreenManager(sge::UIEntityManager* uiEntityManager){ m_uiEntityManagerPtr = uiEntityManager; }

void sge::UIScreenManager::registerUIScreen(std::string name, sge::UIScreen* uiScreen){ 
    for(UIEntity* uiEntity : uiScreen->getUIEntities()){
        m_uiEntityManagerPtr->registerUIEntity(uiEntity);
    }

    m_uiScreens[name] = uiScreen;
}
void sge::UIScreenManager::deregisterUIScreen(std::string name){
    for(UIEntity* uiEntity : m_uiScreens[name]->getUIEntities()){
        m_uiEntityManagerPtr->deregisterUIEntity(uiEntity);
    }

    m_uiScreens.erase(name);
}
sge::UIScreen* sge::UIScreenManager::getUIScreen(std::string name){ return m_uiScreens[name]; }

void sge::UIScreenManager::hideUIScreen(std::string name){
    if(m_uiScreens[name]->isVisible){
        for(UIEntity* uiEntity : m_uiScreens[name]->getUIEntities()){
            m_uiEntityManagerPtr->hideUIEntity(uiEntity);
        }

        m_uiScreens[name]->isVisible = false;
    }
}
void sge::UIScreenManager::showUIScreen(std::string name){
    if(!m_uiScreens[name]->isVisible){
        for(UIEntity* uiEntity : m_uiScreens[name]->getUIEntities()){
            m_uiEntityManagerPtr->showUIEntity(uiEntity);
        }

        m_uiScreens[name]->isVisible = true;
    }
}