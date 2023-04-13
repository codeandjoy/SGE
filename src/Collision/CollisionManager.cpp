#include "CollisionManager.h"
#include "Collision.h"
#include "CollisionUtils.h"

void CollisionManager::registerCollisionShape(CollisionShape* _collisionShape){ allCollisionShapes.push_back(_collisionShape); }

void CollisionManager::deregisterCollisionShape(CollisionShape* _collisionShape){ allCollisionShapes.erase(std::remove(allCollisionShapes.begin(), allCollisionShapes.end(), _collisionShape), allCollisionShapes.end()); }

void CollisionManager::registerCollisionShapes(std::vector<CollisionShape*> _collisionShapes){ allCollisionShapes.insert(allCollisionShapes.end(), _collisionShapes.begin(), _collisionShapes.end()); }

void CollisionManager::degisterCollisionShapes(std::vector<CollisionShape*> _collisionShapes){
    for(CollisionShape* collisionShape : _collisionShapes){
        deregisterCollisionShape(collisionShape);
    }
}



void CollisionManager::registerCollisionGroup(std::string name, std::vector<CollisionShape*> _collisionGroup){ collisionGroups[name] = _collisionGroup; } 

void CollisionManager::deregisterCollisionGroup(std::string name){ collisionGroups.erase(name); }

void CollisionManager::registerCollisionGroups(std::map<std::string, std::vector<CollisionShape*>> _groupsToRegister){ collisionGroups.insert(_groupsToRegister.begin(), _groupsToRegister.end()); }

void CollisionManager::deregisterCollisionGroups(std::map<std::string, std::vector<CollisionShape*>> _groupsToDeregister){
    for(auto& [name, _] : _groupsToDeregister){
        deregisterCollisionGroup(name);
    }
}



void CollisionManager::createCollisionPair(std::string name, std::string group1, std::string group2){
    // TODO Check if both groups exist in collisionGroups
    CollisionPair collisionPair = CollisionPair{std::make_pair(group1, group2)}; 

    for(CollisionShape* initiator : collisionGroups[group1]){
        collisionPair.pastCollisions[initiator] = std::vector<Collision>();
    }

    collisionPairs[name] = collisionPair;
}

void CollisionManager::setCollisionResponse(std::string collisionPairName, std::string collisionPhase, std::function<void(std::vector<Collision>)> response){
    if(collisionPhase == "start_phase"){
        collisionPairs[collisionPairName].startPhaseCollisionResponse = response;
    }
    else if(collisionPhase == "continuous_phase"){
        collisionPairs[collisionPairName].continuousPhaseCollisionResponse = response;
    }
    else if(collisionPhase == "end_phase"){
        collisionPairs[collisionPairName].endPhaseCollisionResponse = response;
    }
}

void CollisionManager::setCollisionDetectionAlgorithm(std::string collisionPairName, std::function<bool(CollisionShape *CS1, CollisionShape *CS2)> cda){
    collisionPairs[collisionPairName].checkCollision = cda;
}

std::vector<CollisionShape*> CollisionManager::getAllCollisionShapes(){ return allCollisionShapes; }

std::map<std::string, std::vector<CollisionShape*>> CollisionManager::getCollisionGroups(){ return collisionGroups; }

void CollisionManager::alignCollisionShapes(){
    for(CollisionShape* collisionShape : allCollisionShapes){
        collisionShape->align();
    }
}

void CollisionManager::updateCollisions(){
    std::vector<Collision> presentCollisions;

    for(auto& [name, pair] : collisionPairs){

        for(CollisionShape* initiator : collisionGroups[pair.collisionGroups.first]){
            // Register all present collisions
            for(CollisionShape* recipient : collisionGroups[pair.collisionGroups.second]){
                if(pair.checkCollision(initiator, recipient)){
                    CollisionSide initiatorImpactSide = determineInitiatorImpactSide(initiator, recipient);

                    presentCollisions.push_back(Collision{
                        initiator,
                        recipient,
                        initiatorImpactSide,
                        flipInitiatorImpactSide(initiatorImpactSide)
                    });
                }
            }


            std::vector<Collision> pastCollisions = pair.pastCollisions[initiator];


            // Determine collision phase
            std::sort(presentCollisions.begin(), presentCollisions.end());
            std::sort(pastCollisions.begin(), pastCollisions.end());

            std::vector<Collision> startPhaseCollisions;
            std::set_difference(presentCollisions.begin(),presentCollisions.end(), pastCollisions.begin(),pastCollisions.end(), std::back_inserter(startPhaseCollisions));

            std::vector<Collision> continuousPhaseCollisions;
            std::set_intersection(pastCollisions.begin(),pastCollisions.end(), presentCollisions.begin(),presentCollisions.end(), std::back_inserter(continuousPhaseCollisions));

            std::vector<Collision> endPhaseCollisions;
            std::set_difference(pastCollisions.begin(),pastCollisions.end(), presentCollisions.begin(),presentCollisions.end(), std::back_inserter(endPhaseCollisions));


            // Run collision responses based on collision phase
            if(startPhaseCollisions.size())
                if(pair.startPhaseCollisionResponse)
                    pair.startPhaseCollisionResponse(startPhaseCollisions);

            if(continuousPhaseCollisions.size())
                if(pair.continuousPhaseCollisionResponse)
                    pair.continuousPhaseCollisionResponse(continuousPhaseCollisions);
            
            if(endPhaseCollisions.size())
                if(pair.endPhaseCollisionResponse)
                    pair.endPhaseCollisionResponse(endPhaseCollisions);


            // Reset
            pair.pastCollisions[initiator] = presentCollisions;
            presentCollisions.clear();
        }
    }
}