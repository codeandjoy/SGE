#include "UISpriteManager.h"

void sge::UISpriteManager::registerSprite(sf::Sprite* sprite){ m_visibleSprites.push_back(sprite); }
void sge::UISpriteManager::deregisterSprite(sf::Sprite* sprite){
    m_visibleSprites.erase(std::remove(m_visibleSprites.begin(), m_visibleSprites.end(), sprite), m_visibleSprites.end());
    m_hiddenSprites.erase(std::remove(m_hiddenSprites.begin(), m_hiddenSprites.end(), sprite), m_hiddenSprites.end());

}
std::vector<sf::Sprite*> sge::UISpriteManager::getAllVisibleSprites(){ return m_visibleSprites; }


void sge::UISpriteManager::showSprite(sf::Sprite* sprite){
    deregisterSprite(sprite);
    m_visibleSprites.push_back(sprite);
}
void sge::UISpriteManager::hideSprite(sf::Sprite* sprite){
    deregisterSprite(sprite);
    m_hiddenSprites.push_back(sprite);
}


void sge::UISpriteManager::drawUISprites(sf::RenderWindow* windowPtr){
    for(sf::Sprite* sprite : m_visibleSprites){
        windowPtr->draw(*sprite);
    }
}