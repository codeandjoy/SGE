#include "UIScreenManager.h"
#include "../UIEntity/UIEntityManager.h"
#include "UIScreen.h"


sge::UIScreenManager::UIScreenManager(sge::UIEntityManager* uiEntityManager){ m_uiEntityManagerPtr = uiEntityManager; }

void sge::UIScreenManager::registerUIScreen(std::string name, sge::UIScreen* uiScreen){ 
    for(sge::UIEntity* uiEntity : uiScreen->getUIEntities()){
        m_uiEntityManagerPtr->registerUIEntity(uiEntity);
    }

    m_uiScreens[name] = uiScreen;
}
void sge::UIScreenManager::deregisterUIScreen(std::string name){
    for(sge::UIEntity* uiEntity : m_uiScreens[name]->getUIEntities()){
        m_uiEntityManagerPtr->deregisterUIEntity(uiEntity);
    }

    m_uiScreens.erase(name);
}
void sge::UIScreenManager::updateUIScreen(std::string name){
    sge::UIScreen* uiScreen = m_uiScreens[name];

    deregisterUIScreen(name);
    registerUIScreen(name, uiScreen);
}
sge::UIScreen* sge::UIScreenManager::getUIScreen(std::string name){ return m_uiScreens[name]; }

void sge::UIScreenManager::hideUIScreen(std::string name){
    if(m_uiScreens[name]->isVisible){
        for(sge::UIEntity* uiEntity : m_uiScreens[name]->getUIEntities()){
            m_uiEntityManagerPtr->hideUIEntity(uiEntity);
        }

        m_uiScreens[name]->isVisible = false;
    }
}
void sge::UIScreenManager::showUIScreen(std::string name){
    if(!m_uiScreens[name]->isVisible){
        for(sge::UIEntity* uiEntity : m_uiScreens[name]->getUIEntities()){
            m_uiEntityManagerPtr->showUIEntity(uiEntity);
        }

        m_uiScreens[name]->isVisible = true;
    }
}