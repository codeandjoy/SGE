#include "CollisionShape.h"

CollisionShape::CollisionShape(PhysicalObject *_owner){
    owner = _owner;

    this->setFillColor(sf::Color(0,0,0,0));
    this->setSize(sf::Vector2f(_owner->getGlobalBounds().width, _owner->getGlobalBounds().height));
    
    this->border.setFillColor(sf::Color(0,0,0,0));
    setBorderColor(sf::Color::Blue);
    setBorderThickness(.5);
}

PhysicalObject* CollisionShape::getOwner(){ return owner; }

CollisionShapePositionData CollisionShape::getPositionData(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}

sf::Vector2f CollisionShape::getOffset(){ return offset; }
void CollisionShape::setOffset(sf::Vector2f _offset){ offset = _offset; }

void CollisionShape::setSize(const sf::Vector2f& size){
    this->RectangleShape::setSize(size);
    border.setSize(sf::Vector2f(size.x-border.getOutlineThickness()*2, size.y-border.getOutlineThickness()*2));
}

// Border
bool CollisionShape::getIsVisible(){ return isVisible; }
void CollisionShape::setIsVisible(bool is){ isVisible = is; }

sf::RectangleShape* CollisionShape::getBorder(){ return &border; }
void CollisionShape::setBorderThickness(float thickness){
    border.setSize(sf::Vector2f(this->getSize().x-thickness*2, this->getSize().y-thickness*2));
    border.setOutlineThickness(thickness);
}
void CollisionShape::setBorderColor(const sf::Color& color){ border.setOutlineColor(color); }
//

void CollisionShape::align(){
    this->setPosition(owner->getPosition() + offset);
    border.setPosition(sf::Vector2f(this->getPosition().x+border.getOutlineThickness(), this->getPosition().y+border.getOutlineThickness()));
}