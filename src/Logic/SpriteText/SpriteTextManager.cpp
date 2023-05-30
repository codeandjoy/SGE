#include <algorithm>

#include "SpriteTextManager.h"
#include "SpriteText.h"


void sge::SpriteTextManager::registerSpriteText(sf::View* view, sge::SpriteText* spriteText){ m_spriteTextObjects[view].push_back(spriteText); }
void sge::SpriteTextManager::deregisterSpriteText(sf::View* view, sge::SpriteText* spriteText){
    m_spriteTextObjects[view].erase(std::remove(m_spriteTextObjects[view].begin(), m_spriteTextObjects[view].end(), spriteText), m_spriteTextObjects[view].end());
}
std::vector<sge::SpriteText*> sge::SpriteTextManager::getSpriteTextObjectsByView(sf::View* view){ return m_spriteTextObjects[view]; }
std::unordered_map<sf::View*, std::vector<sge::SpriteText*>> sge::SpriteTextManager::getSpriteTextObjectsMap(){ return m_spriteTextObjects; }




void sge::SpriteTextManager::alignSpriteTextObjects(){
    for(auto& [_, spriteTextObjects] : m_spriteTextObjects){
        for(sge::SpriteText* spriteText : spriteTextObjects){
            spriteText->align();
        }
    }
}
void sge::SpriteTextManager::drawSpriteTextObjects(sf::RenderWindow* windowPtr){
    for(auto& [view, spriteTextObjects] : m_spriteTextObjects){
        windowPtr->setView(*view);

        for(SpriteText* spriteText : spriteTextObjects){
            windowPtr->draw(*spriteText);
        }
    }
}