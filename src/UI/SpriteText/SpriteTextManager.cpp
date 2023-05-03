#include <algorithm>

#include "SpriteTextManager.h"
#include "SpriteText.h"


void sge::SpriteTextManager::registerSpriteText(sge::SpriteText* spriteText){ m_visibleSpriteTextObjects.push_back(spriteText); }
void sge::SpriteTextManager::deregisterSpriteText(sge::SpriteText* spriteText){
    m_visibleSpriteTextObjects.erase(std::remove(m_visibleSpriteTextObjects.begin(), m_visibleSpriteTextObjects.end(), spriteText), m_visibleSpriteTextObjects.end());
    m_hiddenSpriteTextObjects.erase(std::remove(m_hiddenSpriteTextObjects.begin(), m_hiddenSpriteTextObjects.end(), spriteText), m_hiddenSpriteTextObjects.end());
}
std::vector<sge::SpriteText*> sge::SpriteTextManager::getAllVisibleSpriteTextObjects(){ return m_visibleSpriteTextObjects; }



void sge::SpriteTextManager::showSpriteText(sge::SpriteText* spriteText){
    deregisterSpriteText(spriteText);
    m_visibleSpriteTextObjects.push_back(spriteText);
}
void sge::SpriteTextManager::hideSpriteText(sge::SpriteText* spriteText){
    deregisterSpriteText(spriteText);
    m_hiddenSpriteTextObjects.push_back(spriteText);
}


void sge::SpriteTextManager::alignSpriteTextObjects(){
    for(sge::SpriteText* spriteText : m_visibleSpriteTextObjects){
        spriteText->align();
    }
}