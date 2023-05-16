#include "CollisionResponses.h"
#include "Collision.h"
#include "CollisionSide.h"
#include "../CollisionShape/CollisionShape.h"
#include "../Entity/Entity.h"
#include "../Physics/PhysicalObject.h"


void sge::resolveAABB(std::vector<sge::Collision> collisions){
    for(sge::Collision collision : collisions){
        sge::CollisionShape* initiatorCollisionShape = collision.initiator;
        sge::CollisionShape* recipientCollisionShape = collision.recipient;
        sf::Sprite *initiatorSprite = collision.initiator->getOwnerEntity()->sprite;
        sf::Sprite *recipientSprite = collision.recipient->getOwnerEntity()->sprite;
        
        // Align initiator based on impact side
        if(collision.initiatorImpactSide == sge::CollisionSide::left){
            initiatorSprite->setPosition(
                recipientCollisionShape->getPosition().x + recipientCollisionShape->getGlobalBounds().width - initiatorCollisionShape->offset.x,
                initiatorCollisionShape->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::right){
            initiatorSprite->setPosition(
                recipientCollisionShape->getPosition().x - initiatorCollisionShape->getGlobalBounds().width - initiatorCollisionShape->offset.x,
                initiatorCollisionShape->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::top){
            initiatorSprite->setPosition(
                initiatorCollisionShape->getPosition().x,
                recipientCollisionShape->getPosition().y + recipientCollisionShape->getGlobalBounds().height - initiatorCollisionShape->offset.y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::bottom){
            initiatorSprite->setPosition(
                initiatorCollisionShape->getPosition().x,
                recipientCollisionShape->getPosition().y - initiatorCollisionShape->getGlobalBounds().height - initiatorCollisionShape->offset.y
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