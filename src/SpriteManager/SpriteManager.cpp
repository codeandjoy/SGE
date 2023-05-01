#include "SpriteManager.h"

void sge::SpriteManager::registerSprite(sf::Sprite* sprite){ m_sprites.push_back(sprite); }
void sge::SpriteManager::deregisterSprite(sf::Sprite* sprite){ m_sprites.erase(std::remove(m_sprites.begin(), m_sprites.end(), sprite), m_sprites.end()); }
void sge::SpriteManager::deregisterAllSprites(){ m_sprites.clear(); }
std::vector<sf::Sprite*> sge::SpriteManager::getSprites(){ return m_sprites; }