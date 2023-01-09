#include "SolidObject.h"

SolidObject::SolidObject(sf::Sprite *owner){
    ownerPtr = owner;
    
    updateSolidObject(); // Initialize

    collisionRect.setOutlineColor(sf::Color::Red);
    collisionRect.setOutlineThickness(1);
}

void SolidObject::updateSolidObject(){
    collisionRect.setPosition(ownerPtr->getPosition());
    collisionRect.setSize(sf::Vector2f(ownerPtr->getGlobalBounds().width, ownerPtr->getGlobalBounds().height)); // ! TEMP
}

sf::RectangleShape* SolidObject::getCollisionRect(){
    return &collisionRect;
}