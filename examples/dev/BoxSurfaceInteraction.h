#ifndef BOX_SURFACE_INTERACTION_H
#define BOX_SURFACE_INTERACTION_H

#include "../../SGE.hpp"


class BoxSurfaceInteraction : public sge::CollisionInteraction{
    public:
        BoxSurfaceInteraction(std::vector<std::string> initiatorGroups, std::vector<std::string> recipientGroups) : sge::CollisionInteraction(initiatorGroups, recipientGroups){};

        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }
    
        void continuousPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            sge::MotionUnit* boxMotionUnit = collisions[0].initiator->getOwnerEntity()->motionUnit;

            if(boxMotionUnit->velocity.x){
                if(boxMotionUnit->velocity.x > 0){
                    boxMotionUnit->contactForces["kinetic_friction"] = sf::Vector2f(-200, 0);
                }
                else if(boxMotionUnit->velocity.x < 0){
                    boxMotionUnit->contactForces["kinetic_friction"] = sf::Vector2f(200, 0);
                }
            }
            else if(!boxMotionUnit->velocity.x){
                boxMotionUnit->contactForces.erase("kinetic_friction");
                // static friction (irrelevant atm)
            }
        }

        void endPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            sge::MotionUnit* boxMotionUnit = collisions[0].initiator->getOwnerEntity()->motionUnit;

            boxMotionUnit->contactForces.erase("kinetic_friction");
        }
};



#endif