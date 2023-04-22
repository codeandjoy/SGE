#include "CollisionShape.h"
#include "../Entity/Entity.h"
#include "../utils/Measurements.h"


CollisionShape::CollisionShape(Entity* ownerEntityPtr){
    m_ownerEntityPtr = ownerEntityPtr;

    this->setFillColor(sf::Color(0,0,0,0));
    this->setSize(sf::Vector2f(ownerEntityPtr->physicalObject->getGlobalBounds().width, ownerEntityPtr->physicalObject->getGlobalBounds().height));
}

Entity* CollisionShape::getOwnerEntity(){ return m_ownerEntityPtr; }
Measurements CollisionShape::getMeasurements(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}
void CollisionShape::align(){
    this->setPosition(m_ownerEntityPtr->physicalObject->getPosition() + offset);
}