#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

#include "SFML/Graphics.hpp"
#include "PhysicalObject.h"
#include "CollisionSide.h"
#include "Collision.h"

// ! Assuming PO1 is moveable
// TODO manage moveable and solid objects
void resolveAABB(std::vector<Collision> collisions){
    for(Collision collision : collisions){
        PhysicalObject *from = collision.from;
        PhysicalObject *with = collision.with;
        
        if(collision.side == CollisionSide::left){
            from->setPosition(with->getPosition().x + with->getGlobalBounds().width, from->getPosition().y);
        }
        else if(collision.side == CollisionSide::right){
            from->setPosition(with->getPosition().x - from->getGlobalBounds().width, from->getPosition().y);
        }
        else if(collision.side == CollisionSide::bottom){
            from->setPosition(from->getPosition().x, with->getPosition().y - from->getGlobalBounds().height);
        }
    }
}


#endif