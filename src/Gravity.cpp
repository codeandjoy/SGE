#include <SFML/Graphics.hpp>
#include "Gravity.h"

// owner->setPosition(0, value);
Gravity::Gravity (sf::Vector2f value){
    this->value = value;
}

void Gravity::updatePhysicalProperty(sf::Transformable *owner){
    owner->setPosition(owner->getPosition() + value);
}