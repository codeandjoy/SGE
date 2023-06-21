#ifndef PUSH_INTERACTION_H
#define PUSH_INTERACTION_H

#include "../../SGE.hpp"


class PushInteraction : public sge::CollisionInteraction{
    public:
        PushInteraction(std::vector<std::string> initiatorGroups, std::vector<std::string> recipientGroups, sge::DebugEntity* boxDE) : sge::CollisionInteraction(initiatorGroups, recipientGroups), boxDE(boxDE){};

        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }
    
        void startPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            boxDE->customCollisionShapeBorderSettings["global_bounds"] = sge::CollisionShapeBorderSettings{sf::Color::Red};

            for(sge::Collision collision : collisions){
                if(collision.recipientImpactSide == sge::CollisionSide::right){
                    // collision.recipient->getOwnerEntity()->motionUnit->velocity.x = -30;
                    collision.recipient->getOwnerEntity()->motionUnit->contactForces["push"] = sf::Vector2f(-300, 0);
                }
                else if(collision.recipientImpactSide == sge::CollisionSide::left){
                    collision.recipient->getOwnerEntity()->motionUnit->contactForces["push"] = sf::Vector2f(300, 0);
                }
            }    

        }

        void endPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            boxDE->customCollisionShapeBorderSettings["global_bounds"] = sge::CollisionShapeBorderSettings{sf::Color::Green};
        
            for(sge::Collision collision : collisions){
                collision.recipient->getOwnerEntity()->motionUnit->contactForces.erase("push");
            }          

        }
    
    private:
        sge::DebugEntity* boxDE;
};


#endif