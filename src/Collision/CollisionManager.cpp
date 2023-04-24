#include "CollisionManager.h"
#include "Collision.h"
#include "CollisionUtils.h"
#include "CollisionPair.h"
#include "CollisionShape.h"



void sge::CollisionManager::registerCollisionShape(sge::CollisionShape* collisionShape){ m_allCollisionShapes.push_back(collisionShape); }
void sge::CollisionManager::deregisterCollisionShape(sge::CollisionShape* collisionShape){ m_allCollisionShapes.erase(std::remove(m_allCollisionShapes.begin(), m_allCollisionShapes.end(), collisionShape), m_allCollisionShapes.end()); }
void sge::CollisionManager::registerCollisionShapes(std::vector<sge::CollisionShape*> collisionShapes){ m_allCollisionShapes.insert(m_allCollisionShapes.end(), collisionShapes.begin(), collisionShapes.end()); }
void sge::CollisionManager::degisterCollisionShapes(std::vector<sge::CollisionShape*> collisionShapes){
    for(sge::CollisionShape* collisionShape : collisionShapes){
        deregisterCollisionShape(collisionShape);
    }
}
std::vector<sge::CollisionShape*> sge::CollisionManager::getAllCollisionShapes(){ return m_allCollisionShapes; }
void sge::CollisionManager::alignCollisionShapes(){
    for(sge::CollisionShape* collisionShape : m_allCollisionShapes){
        collisionShape->align();
    }
}



void sge::CollisionManager::registerCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionGroup){ m_collisionGroups[name] = collisionGroup; } 
void sge::CollisionManager::deregisterCollisionGroup(std::string name){ m_collisionGroups.erase(name); }
void sge::CollisionManager::registerCollisionGroups(std::unordered_map<std::string, std::vector<sge::CollisionShape*>> collisionGroups){ m_collisionGroups.insert(collisionGroups.begin(), collisionGroups.end()); }
void sge::CollisionManager::deregisterCollisionGroups(std::unordered_map<std::string, std::vector<sge::CollisionShape*>> collisionGroups){
    for(auto& [name, _] : collisionGroups){
        deregisterCollisionGroup(name);
    }
}
std::unordered_map<std::string, std::vector<sge::CollisionShape*>> sge::CollisionManager::getCollisionGroups(){ return m_collisionGroups; }



void sge::CollisionManager::createCollisionPair(std::string name, std::string initiatorGroup, std::string recipientGroup){
    if(!m_collisionGroups.count(initiatorGroup) && !m_collisionGroups.count(recipientGroup)){
        printf("Can not create %s - %s collision m_collisionPairs[pair].", initiatorGroup.c_str(), recipientGroup.c_str());
        exit(1);
    }

    m_collisionPairs[name] = new sge::CollisionPair{std::make_pair(initiatorGroup, recipientGroup)};
    m_collisionPairsOrder.push_back(name);
}
void sge::CollisionManager::setPairCollisionDetectionAlgorithm(std::string collisionPairName, std::function<bool(sge::CollisionShape*, sge::CollisionShape*)> collisionDetectionAlgorithm){ m_collisionPairs[collisionPairName]->checkCollision = collisionDetectionAlgorithm; }
void sge::CollisionManager::setPairCollisionResponse(std::string collisionPairName, std::string collisionPhase, std::function<void(std::vector<sge::Collision>)> response){
    if(collisionPhase == "start_phase"){
        m_collisionPairs[collisionPairName]->startPhaseCollisionResponse = response;
    }
    else if(collisionPhase == "continuous_phase"){
        m_collisionPairs[collisionPairName]->continuousPhaseCollisionResponse = response;
    }
    else if(collisionPhase == "end_phase"){
        m_collisionPairs[collisionPairName]->endPhaseCollisionResponse = response;
    }
}





void sge::CollisionManager::updateCollisions(){
    std::vector<sge::Collision> presentCollisions;

    // TODO check in order of insertion ?
    for(std::string pair : m_collisionPairsOrder){

        for(sge::CollisionShape* initiator : m_collisionGroups[m_collisionPairs[pair]->collisionGroups.first]){
            // Register all present collisions
            for(sge::CollisionShape* recipient : m_collisionGroups[m_collisionPairs[pair]->collisionGroups.second]){
                if(m_collisionPairs[pair]->checkCollision(initiator, recipient)){
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

            // std::vector<sge::Collision> startPhaseCollisions;
            // std::set_difference(presentCollisions.begin(),presentCollisions.end(), pastCollisions.begin(),pastCollisions.end(), std::back_inserter(startPhaseCollisions));

            // std::vector<sge::Collision> continuousPhaseCollisions;
            // std::set_intersection(pastCollisions.begin(),pastCollisions.end(), presentCollisions.begin(),presentCollisions.end(), std::back_inserter(continuousPhaseCollisions));

            // std::vector<sge::Collision> endPhaseCollisions;
            // std::set_difference(pastCollisions.begin(),pastCollisions.end(), presentCollisions.begin(),presentCollisions.end(), std::back_inserter(endPhaseCollisions));

            // Either works

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