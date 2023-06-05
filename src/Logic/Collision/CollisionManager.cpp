#include <algorithm>
#include "CollisionManager.h"
#include "Collision.h"
#include "CollisionUtils.h"
#include "CollisionInteraction.h"
#include "../CollisionShape/CollisionShape.h"
#include "../CollisionShape/CollisionShapeManager.h"


void sge::CollisionManager::updateCollisions(){
    std::vector<sge::Collision> presentCollisions;

    for(CollisionInteraction* collisionInteraction : m_components){
        for(std::string initiatorGroup : collisionInteraction->initiatorGroups){
            for(sge::CollisionShape* initiator : m_collisionShapeManagerPtr->getComponentsByCollisionGroup(initiatorGroup)){
                if(!initiator->isActive) continue;

                // Collect all present collisions
                for(std::string recipientGroup : collisionInteraction->recipientGroups){
                    for(sge::CollisionShape* recipient : m_collisionShapeManagerPtr->getComponentsByCollisionGroup(recipientGroup)){
                        if(!recipient->isActive) continue;

                        if(collisionInteraction->collisionDetectionAlgorithm(initiator, recipient)){
                            CollisionSide initiatorImpactSide = determineInitiatorImpactSide(initiator, recipient);

                            presentCollisions.push_back(sge::Collision{
                                initiator,
                                recipient,
                                initiatorImpactSide,
                                flipInitiatorImpactSide(initiatorImpactSide)
                            });
                        }
                    }
                }
                //


                std::vector<sge::Collision> pastCollisions = collisionInteraction->pastCollisions[initiator];


                // Determine collision phase
                std::sort(presentCollisions.begin(), presentCollisions.end());
                std::sort(pastCollisions.begin(), pastCollisions.end());


                std::vector<sge::Collision> continuousPhaseCollisions;
                std::set_intersection(pastCollisions.begin(),pastCollisions.end(), presentCollisions.begin(),presentCollisions.end(), std::back_inserter(continuousPhaseCollisions));

                std::vector<sge::Collision> startPhaseCollisions;
                std::set_difference(presentCollisions.begin(),presentCollisions.end(), continuousPhaseCollisions.begin(),continuousPhaseCollisions.end(), std::back_inserter(startPhaseCollisions));

                std::vector<sge::Collision> endPhaseCollisions;
                std::set_difference(pastCollisions.begin(),pastCollisions.end(), continuousPhaseCollisions.begin(),continuousPhaseCollisions.end(), std::back_inserter(endPhaseCollisions));
                //


                // Run collision responses based on collision phase
                if(startPhaseCollisions.size())
                    collisionInteraction->startPhaseCollisionResponse(startPhaseCollisions);

                if(continuousPhaseCollisions.size())
                    collisionInteraction->continuousPhaseCollisionResponse(continuousPhaseCollisions);
                
                if(endPhaseCollisions.size())
                    collisionInteraction->endPhaseCollisionResponse(endPhaseCollisions);
                //


                // Reset
                collisionInteraction->pastCollisions[initiator] = presentCollisions;
                presentCollisions.clear();
                //
            }
        }
    }
}