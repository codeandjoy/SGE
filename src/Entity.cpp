#include "Entity.h"

Entity::Entity(){
    this->setSize(Vector2f(40, 40));
    this->setPosition(Vector2f(100, 100));
    this->setFillColor(Color::Red);
}