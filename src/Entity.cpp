#include "Entity.h"

Entity::Entity(){
    // TODO hardcoded properties
    this->setSize(sf::Vector2f(40, 40));
    this->setPosition(sf::Vector2f(100, 100));
    this->setFillColor(sf::Color::Red);
}

void Entity::setIsMovingTop(bool is){ isMovingTop = is; }
void Entity::setIsMovingBottom(bool is){ isMovingBottom = is; }
void Entity::setIsMovingRight(bool is){ isMovingRight = is; }
void Entity::setIsMovingLeft(bool is){ isMovingLeft = is; }

void Entity::update(){
    // TODO hardcoded velocity
    if(isMovingTop) move(sf::Vector2f(0, 1));
    if(isMovingBottom) move(sf::Vector2f(0, -1));
    if(isMovingRight) move(sf::Vector2f(1, 0));
    if(isMovingLeft) move(sf::Vector2f(-1, 0));
}

void Entity::move(sf::Vector2f movement){
    this->setPosition(this->getPosition() + movement);
}