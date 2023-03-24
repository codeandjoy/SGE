#include "CollisionShape.h"

CollisionShape::CollisionShape(PhysicalObject *_owner){
    owner = _owner;

    this->setFillColor(sf::Color(0,0,0,0));
    this->setSize(sf::Vector2f(_owner->getGlobalBounds().width, _owner->getGlobalBounds().height));
    this->setOutlineColor(sf::Color::Blue);
    this->setOutlineThickness(.5);
}

PhysicalObject* CollisionShape::getOwner(){ return owner; }

CollisionShapePositionData CollisionShape::getPositionData(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}

bool CollisionShape::getIsVisible(){ return isVisible; }
void CollisionShape::setIsVisible(bool is){ isVisible = is; }

sf::Vector2f CollisionShape::getOffset(){ return offset; }
void CollisionShape::setOffset(sf::Vector2f _offset){ offset = _offset; }

void CollisionShape::align(){
    this->setPosition(owner->getPosition() + offset);
}