#include "CollisionShape.h"

CollisionShape::CollisionShape(PhysicalObject *owner){
    m_owner = owner;

    this->setFillColor(sf::Color(0,0,0,0));
    this->setSize(sf::Vector2f(owner->getGlobalBounds().width, owner->getGlobalBounds().height));
}

PhysicalObject* CollisionShape::getOwner(){ return m_owner; }
Measurements CollisionShape::getMeasurements(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}
void CollisionShape::align(){
    this->setPosition(m_owner->getPosition() + offset);
}