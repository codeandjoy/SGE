#include "CollisionShape.h"

CollisionShape::CollisionShape(PhysicalObject *_owner){
    owner = _owner;

    this->setFillColor(sf::Color(0,0,0,0));
    this->setSize(sf::Vector2f(_owner->getGlobalBounds().width, _owner->getGlobalBounds().height));
}

PhysicalObject* CollisionShape::getOwner(){ return owner; }

Measurements CollisionShape::getMeasurements(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}

void CollisionShape::align(){
    this->setPosition(owner->getPosition() + offset);
}