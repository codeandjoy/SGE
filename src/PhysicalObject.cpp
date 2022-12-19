#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(sf::Transformable *owner){
    this->owner = owner;
}

void PhysicalObject::addPhysicalProperty(PhysicalProperty *property){
    physicalProperties.push_back(property);
}

void PhysicalObject::updatePhysics(){
    for(PhysicalProperty *property : physicalProperties){
        property->updatePhysicalProperty(owner);
    }
}