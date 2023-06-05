#include <algorithm>
#include "CollisionManager.h"
#include "Collision.h"
#include "CollisionUtils.h"
#include "CollisionPair.h"
#include "../CollisionShape/CollisionShape.h"
#include "../CollisionShape/CollisionShapeManager.h"


void sge::CollisionManager::registerCollisionPair(std::string name, sge::CollisionPair* collisionPair){
    m_collisionPairs[name] = collisionPair;
    m_collisionPairsOrder.push_back(name);
};
void sge::CollisionManager::registerCollisionPairs(std::unordered_map<std::string, CollisionPair*> collisionPairs){ m_collisionPairs.insert(collisionPairs.begin(), collisionPairs.end()); }
void sge::CollisionManager::setCollisionPairsOrder(std::vector<std::string> order){ m_collisionPairsOrder = order; }
void sge::CollisionManager::deregisterCollisionPair(std::string name){
    m_collisionPairs.erase(name);
    m_collisionPairsOrder.erase(std::remove(m_collisionPairsOrder.begin(), m_collisionPairsOrder.end(), name), m_collisionPairsOrder.end());
}


void sge::CollisionManager::updateCollisions(){
    std::vector<sge::Collision> presentCollisions;

    for(std::string pair : m_collisionPairsOrder){

        for(sge::CollisionShape* initiator : m_collisionShapeManagerPtr->getComponentsByCollisionGroup(m_collisionPairs[pair]->initiatorGroupName)){
            if(!initiator->isActive) continue;

            // Collect all present collisions
            for(sge::CollisionShape* recipient : m_collisionShapeManagerPtr->getComponentsByCollisionGroup(m_collisionPairs[pair]->recipientGroupName)){
                if(!recipient->isActive) continue;

                if(m_collisionPairs[pair]->algorithm(initiator, recipient)){
                    CollisionSide initiatorImpactSide = determineInitiatorImpactSide(initiator, recipient);

                    presentCollisions.push_back(sge::Collision{
                        initiator,
                        recipient,
                        initiatorImpactSide,
                        flipInitiatorImpactSide(initiatorImpactSide)
                    });
                }
            }
            //


            std::vector<sge::Collision> pastCollisions = m_collisionPairs[pair]->pastCollisions[initiator];


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
                if(m_collisionPairs[pair]->startPhaseCollisionResponse)
                    m_collisionPairs[pair]->startPhaseCollisionResponse(startPhaseCollisions);

            if(continuousPhaseCollisions.size())
                if(m_collisionPairs[pair]->continuousPhaseCollisionResponse)
                    m_collisionPairs[pair]->continuousPhaseCollisionResponse(continuousPhaseCollisions);
            
            if(endPhaseCollisions.size())
                if(m_collisionPairs[pair]->endPhaseCollisionResponse)
                    m_collisionPairs[pair]->endPhaseCollisionResponse(endPhaseCollisions);
            //


            // Reset
            m_collisionPairs[pair]->pastCollisions[initiator] = presentCollisions;
            presentCollisions.clear();
            //
        }
    }
}