#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

#include "CollisionSide.h"
#include "Collision.h"
#include "CollisionShape.h"
#include "CollisionUtils.h"
#include "../Physics/PhysicalObject.h"


void resolveAABB(std::vector<Collision> collisions){
    for(Collision collision : collisions){
        PhysicalObject *fromOwner = collision.from->getOwner();
        PhysicalObject *withOwner = collision.with->getOwner();
        
        if(collision.side == CollisionSide::left){
            fromOwner->setPosition(
                withOwner->getPosition().x + withOwner->getGlobalBounds().width - collision.from->getOffset().x,
                fromOwner->getPosition().y
            );
        }
        else if(collision.side == CollisionSide::right){
            fromOwner->setPosition(
                withOwner->getPosition().x - collision.from->getGlobalBounds().width - collision.from->getOffset().x,
                fromOwner->getPosition().y
            );
        }
        else if(collision.side == CollisionSide::top){
            fromOwner->setPosition(
                fromOwner->getPosition().x,
                withOwner->getPosition().y + withOwner->getGlobalBounds().height - collision.from->getOffset().y
            );
        }
        else if(collision.side == CollisionSide::bottom){
            fromOwner->setPosition(
                fromOwner->getPosition().x,
                withOwner->getPosition().y - collision.from->getGlobalBounds().height - collision.from->getOffset().y
            );
        }
    }
}


#endif