#include "SolidObject.h"

SolidObject::SolidObject(sf::Sprite *owner){
    ownerPtr = owner;
    
    updateSolidObject(); // init

    // TODO allow to set manually
    collisionRect.setFillColor(sf::Color(0, 0, 0, 0));
    collisionRect.setOutlineColor(sf::Color::Red);
    collisionRect.setOutlineThickness(.5);
}

void SolidObject::updateSolidObject(){
    collisionRect.setPosition(ownerPtr->getPosition());
    collisionRect.setSize(sf::Vector2f(ownerPtr->getGlobalBounds().width, ownerPtr->getGlobalBounds().height)); // ! TEMP
}

sf::RectangleShape* SolidObject::getCollisionRect(){
    return &collisionRect;
}