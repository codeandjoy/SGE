#include "SpriteText.h"

sge::SpriteText::SpriteText(sf::Sprite* ownerSprite){ m_ownerSpritePtr = ownerSprite; }
void sge::SpriteText::align(){
    sf::Vector2f pos = m_ownerSpritePtr->getPosition() + offset; 
    
    this->setPosition((int)pos.x, (int)pos.y);
}