#include "CollisionResponses.h"
#include "Collision.h"
#include "CollisionSide.h"
#include "CollisionShape.h"
#include "../Entity/Entity.h"
#include "../Physics/PhysicalObject.h"


void sge::resolveAABB(std::vector<sge::Collision> collisions){
    for(sge::Collision collision : collisions){
        sge::PhysicalObject *initiatorPhysicalObject = collision.initiator->getOwnerEntity()->physicalObject;
        sge::PhysicalObject *recipientPhysicalObject = collision.recipient->getOwnerEntity()->physicalObject;
        
        // Align initiator based on impact side
        if(collision.initiatorImpactSide == sge::CollisionSide::left){
            initiatorPhysicalObject->setPosition(
                recipientPhysicalObject->getPosition().x + recipientPhysicalObject->getGlobalBounds().width - collision.initiator->offset.x,
                initiatorPhysicalObject->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::right){
            initiatorPhysicalObject->setPosition(
                recipientPhysicalObject->getPosition().x - collision.initiator->getGlobalBounds().width - collision.initiator->offset.x,
                initiatorPhysicalObject->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::top){
            initiatorPhysicalObject->setPosition(
                initiatorPhysicalObject->getPosition().x,
                recipientPhysicalObject->getPosition().y + recipientPhysicalObject->getGlobalBounds().height - collision.initiator->offset.y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::bottom){
            initiatorPhysicalObject->setPosition(
                initiatorPhysicalObject->getPosition().x,
                recipientPhysicalObject->getPosition().y - collision.initiator->getGlobalBounds().height - collision.initiator->offset.y
            );
        }
        //
    }
}

void sge::initiatorStandOnTopOfRecipient(std::vector<sge::Collision> collisions){
    for(sge::Collision collision : collisions){
        if(collision.initiatorImpactSide == sge::CollisionSide::bottom){
            collision.initiator->getOwnerEntity()->physicalObject->velocity.y = 0;
        }
    }
}