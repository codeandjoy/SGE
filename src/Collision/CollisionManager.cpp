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
    collisionPairs[name] = CollisionPair{std::make_tuple(group1, group2)};
}

void CollisionManager::addCollisionResponse(std::string collisionPairName, const std::function<void(std::vector<Collision>)> &response){
    collisionPairs[collisionPairName].collisionResponses.push_back(response);
}

void CollisionManager::setCollisionDetectionAlgorithm(std::string collisionPairName, const std::function<bool(CollisionShape *CS1, CollisionShape *CS2)> &cda){
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
    std::vector<Collision> collisions;

    for(auto const& [name, pair] : collisionPairs){
        for(CollisionShape* initiator : collisionGroups[std::get<0>(pair.collisionGroups)]){
            for(CollisionShape* recipient : collisionGroups[std::get<1>(pair.collisionGroups)]){
                if(pair.checkCollision(initiator, recipient)){
                    CollisionSide initiatorImpactSide = determineInitiatorImpactSide(initiator, recipient);

                    collisions.push_back(Collision{
                        initiator,
                        recipient,
                        initiatorImpactSide,
                        flipInitiatorImpactSide(initiatorImpactSide)
                    });
                }
            }

            // Run collision responses
            if(collisions.size()){
                for(std::function collisionResponse : pair.collisionResponses){
                    collisionResponse(collisions);
                }
            }

            // Reset
            collisions.clear();
        }
    }
}