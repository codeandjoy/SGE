#include "CollisionShape.h"
#include "../Entity/Entity.h"
#include "../utils/Measurements.h"


sge::CollisionShape::CollisionShape(sge::Entity* ownerEntityPtr){
    m_ownerEntityPtr = ownerEntityPtr;

    this->setFillColor(sf::Color(0,0,0,0));
    this->setSize(sf::Vector2f(ownerEntityPtr->physicalObject->getGlobalBounds().width, ownerEntityPtr->physicalObject->getGlobalBounds().height));
}

sge::Entity* sge::CollisionShape::getOwnerEntity(){ return m_ownerEntityPtr; }
sge::Measurements sge::CollisionShape::getMeasurements(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}
void sge::CollisionShape::align(){
    this->setPosition(m_ownerEntityPtr->physicalObject->getPosition() + offset);
}