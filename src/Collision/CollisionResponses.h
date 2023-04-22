#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

#include "Collision.h"
#include "CollisionSide.h"
#include "../Physics/PhysicalObject.h"


void resolveAABB(std::vector<Collision> collisions){
    for(Collision collision : collisions){
        PhysicalObject *initiatorPhysicalObject = collision.initiator->getOwnerEntity()->physicalObject;
        PhysicalObject *recipientPhysicalObject = collision.recipient->getOwnerEntity()->physicalObject;
        
        // Align initiator based on impact side
        if(collision.initiatorImpactSide == CollisionSide::left){
            initiatorPhysicalObject->setPosition(
                recipientPhysicalObject->getPosition().x + recipientPhysicalObject->getGlobalBounds().width - collision.initiator->offset.x,
                initiatorPhysicalObject->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == CollisionSide::right){
            initiatorPhysicalObject->setPosition(
                recipientPhysicalObject->getPosition().x - collision.initiator->getGlobalBounds().width - collision.initiator->offset.x,
                initiatorPhysicalObject->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == CollisionSide::top){
            initiatorPhysicalObject->setPosition(
                initiatorPhysicalObject->getPosition().x,
                recipientPhysicalObject->getPosition().y + recipientPhysicalObject->getGlobalBounds().height - collision.initiator->offset.y
            );
        }
        else if(collision.initiatorImpactSide == CollisionSide::bottom){
            initiatorPhysicalObject->setPosition(
                initiatorPhysicalObject->getPosition().x,
                recipientPhysicalObject->getPosition().y - collision.initiator->getGlobalBounds().height - collision.initiator->offset.y
            );
        }
        //
    }
}

void initiatorStandOnTopOfRecipient(std::vector<Collision> collisions){
    for(Collision collision : collisions){
        if(collision.initiatorImpactSide == CollisionSide::bottom){
            collision.initiator->getOwnerEntity()->physicalObject->velocity.y = 0;
        }
    }
}


#endif