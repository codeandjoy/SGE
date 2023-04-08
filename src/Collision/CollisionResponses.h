#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

#include "Collision.h"
#include "CollisionSide.h"
#include "../Physics/PhysicalObject.h"


void resolveAABB(std::vector<Collision> collisions){
    for(Collision collision : collisions){
        PhysicalObject *initiatorOwner = collision.initiator->getOwner();
        PhysicalObject *recipientOwner = collision.recipient->getOwner();
        
        // Align initiator based on impact side
        if(collision.initiatorImpactSide == CollisionSide::left){
            initiatorOwner->setPosition(
                recipientOwner->getPosition().x + recipientOwner->getGlobalBounds().width - collision.initiator->offset.x,
                initiatorOwner->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == CollisionSide::right){
            initiatorOwner->setPosition(
                recipientOwner->getPosition().x - collision.initiator->getGlobalBounds().width - collision.initiator->offset.x,
                initiatorOwner->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == CollisionSide::top){
            initiatorOwner->setPosition(
                initiatorOwner->getPosition().x,
                recipientOwner->getPosition().y + recipientOwner->getGlobalBounds().height - collision.initiator->offset.y
            );
        }
        else if(collision.initiatorImpactSide == CollisionSide::bottom){
            initiatorOwner->setPosition(
                initiatorOwner->getPosition().x,
                recipientOwner->getPosition().y - collision.initiator->getGlobalBounds().height - collision.initiator->offset.y
            );
        }
    }
}

void initiatorStandOnTopOfRecipient(std::vector<Collision> collisions){
    for(Collision collision : collisions){
        if(collision.initiatorImpactSide == CollisionSide::bottom){
            collision.initiator->getOwner()->velocity.y = 0;
        }
    }
}


#endif