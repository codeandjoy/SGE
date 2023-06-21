#ifndef PLAYER_SURFACE_INTERACTION
#define PLAYER_SURFACE_INTERACTION

#include "../../SGE.hpp"


class PlayerSurfaceInteraction : public sge::CollisionInteraction{
    public:
        PlayerSurfaceInteraction(std::vector<std::string> initiatorGroups, std::vector<std::string> recipientGroups) : sge::CollisionInteraction(initiatorGroups, recipientGroups){};

        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }
    
        void startPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            sge::StateCluster* playerStateCluster = collisions[0].initiator->getOwnerEntity()->stateCluster;
            
            playerStateCluster->deactivateState("jump");
            playerStateCluster->activateState("on_ground");
        }
};


#endif