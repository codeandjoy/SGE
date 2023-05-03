#include "UIEntityManager.h"
#include "../UISpriteManager/UISpriteManager.h"
#include "../ClickableShape/ClickableShapeManager.h"
#include "../SpriteText/SpriteTextManager.h"
#include "../UIAnimationManager/UIAnimationManager.h"
#include "../UIEntity/UIEntity.h"


sge::UIEntityManager::UIEntityManager(sge::UISpriteManager* uiSpriteManager, sge::ClickableShapeManager* clickableShapeManager, sge::SpriteTextManager* spriteTextManager, sge::UIAnimationManager* uiAnimationManager){
    m_uiSpriteManager = uiSpriteManager;
    m_clickableShapeManager = clickableShapeManager;
    m_spriteTextManager = spriteTextManager;
    m_uiAnimationManager = uiAnimationManager;
}



void sge::UIEntityManager::registerUIEntity(sge::UIEntity* uiEntity){
    m_uiSpriteManager->registerSprite(uiEntity->sprite);

    if(uiEntity->clickableShape){
        m_clickableShapeManager->registerClickableShape(uiEntity->clickableShape);
    }

    if(uiEntity->spriteText){
        m_spriteTextManager->registerSpriteText(uiEntity->spriteText);
    }

    if(uiEntity->animation){
        m_uiAnimationManager->registerAnimation(uiEntity->animation);
    }

    m_uiEntities.push_back(uiEntity);
}
void sge::UIEntityManager::deregisterUIEntity(sge::UIEntity* uiEntity){
    m_uiSpriteManager->deregisterSprite(uiEntity->sprite);

    if(uiEntity->clickableShape){
        m_clickableShapeManager->deregsiterClickableShape(uiEntity->clickableShape);
    }

    if(uiEntity->spriteText){
        m_spriteTextManager->deregisterSpriteText(uiEntity->spriteText);
    }

    if(uiEntity->animation){
        m_uiAnimationManager->deregisterAnimation(uiEntity->animation);
    }

    m_uiEntities.erase(std::remove(m_uiEntities.begin(), m_uiEntities.end(), uiEntity), m_uiEntities.end());
}
void sge::UIEntityManager::deregisterAllUIEntities(){
    for(sge::UIEntity* uiEntity : m_uiEntities){
        deregisterUIEntity(uiEntity);
    }
}



void sge::UIEntityManager::showUIEntity(sge::UIEntity* uiEntity){
    m_uiSpriteManager->showSprite(uiEntity->sprite);

    if(uiEntity->clickableShape){
        m_clickableShapeManager->activateClickableShape(uiEntity->clickableShape);
    }

    if(uiEntity->spriteText){
        m_spriteTextManager->showSpriteText(uiEntity->spriteText);
    }

    if(uiEntity->animation){
        m_uiAnimationManager->activateAnimation(uiEntity->animation);
    }
}
void sge::UIEntityManager::hideUIEntity(sge::UIEntity* uiEntity){
    m_uiSpriteManager->hideSprite(uiEntity->sprite);

    if(uiEntity->clickableShape){
        m_clickableShapeManager->deactivateClickableShape(uiEntity->clickableShape);
    }

    if(uiEntity->spriteText){
        m_spriteTextManager->hideSpriteText(uiEntity->spriteText);
    }

    if(uiEntity->animation){
        m_uiAnimationManager->deactivateAnimation(uiEntity->animation);
    }
}