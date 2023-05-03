#include "UISpriteManager.h"

void sge::UISpriteManager::registerSprite(sf::Sprite* sprite){ m_visibleSprites.push_back(sprite); }
void sge::UISpriteManager::deregisterSprite(sf::Sprite* sprite){
    m_visibleSprites.erase(std::remove(m_visibleSprites.begin(), m_visibleSprites.end(), sprite), m_visibleSprites.end());
    m_hiddenSprites.erase(std::remove(m_hiddenSprites.begin(), m_hiddenSprites.end(), sprite), m_hiddenSprites.end());

}



void sge::UISpriteManager::showSprite(sf::Sprite* sprite){
    deregisterSprite(sprite);
    m_visibleSprites.push_back(sprite);
}
void sge::UISpriteManager::hideSprite(sf::Sprite* sprite){
    deregisterSprite(sprite);
    m_hiddenSprites.push_back(sprite);
}