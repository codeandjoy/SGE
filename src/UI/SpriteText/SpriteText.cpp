#include "SpriteText.h"

sge::SpriteText::SpriteText(sf::Sprite* ownerSprite){ m_ownerSpritePtr = ownerSprite; }
void sge::SpriteText::align(){
    this->setPosition(m_ownerSpritePtr->getPosition() + offset);
}