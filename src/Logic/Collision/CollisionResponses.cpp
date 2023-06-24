#include "CollisionResponses.h"
#include "Collision.h"
#include "CollisionSide.h"
#include "../CollisionShape/CollisionShape.h"
#include "../Entity/Entity.h"
#include "../Sprite/Sprite.h"
#include "../Physics/MotionUnit.h"


void sge::resolveAABB(std::vector<sge::Collision> collisions){
    for(sge::Collision collision : collisions){
        sge::Sprite *initiatorSprite = collision.initiator->getOwnerEntity()->sprite;
        sge::Sprite *recipientSprite = collision.recipient->getOwnerEntity()->sprite;
        
        // Align initiator based on impact side
        if(collision.initiatorImpactSide == sge::CollisionSide::left){
            initiatorSprite->setPosition(
                recipientSprite->getPosition().x + collision.recipient->getGlobalBounds().width - collision.initiator->offset.x + collision.recipient->offset.x,
                initiatorSprite->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::right){
            initiatorSprite->setPosition(
                recipientSprite->getPosition().x - collision.initiator->getGlobalBounds().width - collision.initiator->offset.x + collision.recipient->offset.x,
                initiatorSprite->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::top){
            initiatorSprite->setPosition(
                initiatorSprite->getPosition().x,
                recipientSprite->getPosition().y + collision.recipient->getGlobalBounds().height - collision.initiator->offset.y + collision.recipient->offset.y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::bottom){
            initiatorSprite->setPosition(
                initiatorSprite->getPosition().x,
                recipientSprite->getPosition().y - collision.initiator->getGlobalBounds().height - collision.initiator->offset.y + collision.recipient->offset.y
            );
        }
        //
    }
}

void sge::initiatorStandOnTopOfRecipient(std::vector<sge::Collision> collisions){
    for(sge::Collision collision : collisions){
        if(collision.initiatorImpactSide == sge::CollisionSide::bottom){
            collision.initiator->getOwnerEntity()->motionUnit->velocity.y = 0;
        }
    }
}