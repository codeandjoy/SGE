#include "SpriteManager.h"

void sge::SpriteManager::registerSprite(sf::View* view, sf::Sprite* sprite){ m_sprites[view].push_back(sprite); }
void sge::SpriteManager::deregisterSprite(sf::View* view, sf::Sprite* sprite){ m_sprites[view].erase(std::remove(m_sprites[view].begin(), m_sprites[view].end(), sprite), m_sprites[view].end()); }
void sge::SpriteManager::deregisterAllSprites(){ m_sprites.clear(); }
std::vector<sf::Sprite*> sge::SpriteManager::getViewSprites(sf::View* view){ return m_sprites[view]; }

void sge::SpriteManager::drawSprites(sf::RenderWindow* windowPtr){
    for(auto [view, sprites] : m_sprites){
        windowPtr->setView(*view);

        for(sf::Sprite* sprite : sprites){
            windowPtr->draw(*sprite);
        }
    }
}