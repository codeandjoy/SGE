#include "Entity.h"

Entity::Entity(){
    // TODO hardcoded properties
    this->setSize(Vector2f(40, 40));
    this->setPosition(Vector2f(100, 100));
    this->setFillColor(Color::Red);
}

void Entity::setIsMovingTop(bool is){ isMovingTop = is; }
void Entity::setIsMovingBottom(bool is){ isMovingBottom = is; }
void Entity::setIsMovingRight(bool is){ isMovingRight = is; }
void Entity::setIsMovingLeft(bool is){ isMovingLeft = is; }

void Entity::update(){
    // TODO hardcoded velocity
    if(isMovingTop) move(Vector2f(0, 1));
    if(isMovingBottom) move(Vector2f(0, -1));
    if(isMovingRight) move(Vector2f(1, 0));
    if(isMovingLeft) move(Vector2f(-1, 0));
}

void Entity::move(Vector2f movement){
    this->setPosition(this->getPosition() + movement);
}