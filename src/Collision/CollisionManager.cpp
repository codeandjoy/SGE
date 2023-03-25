#include "CollisionManager.h"
#include "Collision.h"
#include "CollisionUtils.h"

void CollisionManager::registerCollisionGroup(std::string name, CollisionGroup* _collisionGroup){ collisionGroups[name] = _collisionGroup; } 

void CollisionManager::deregisterCollisionGroup(std::string name){ collisionGroups.erase(name); }

void CollisionManager::registerCollisionGroups(std::map<std::string, CollisionGroup*> _groupsToRegister){ collisionGroups.insert(_groupsToRegister.begin(), _groupsToRegister.end()); }

void CollisionManager::deregisterCollisionGroups(std::map<std::string, CollisionGroup*> _groupsToDeregister){
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

std::map<std::string, CollisionGroup*> CollisionManager::getCollisionGroups(){ return collisionGroups; }

void CollisionManager::updateCollisions(){
    // Aligh collision shapes
    for(auto& [key, collisionGroup] : collisionGroups){
        for(CollisionShape *collisionShape : collisionGroup->collisionShapes){
            collisionShape->align();
        }
    }
    //

    // TODO check if any collision pairs are added

    std::vector<Collision> collisions;

    // TODO refactor ?
    for(auto const& [name, pair] : collisionPairs){
        // Determine all collisions
        for(CollisionShape *collisionShape_Group1 : collisionGroups[std::get<0>(pair.collisionGroups)]->collisionShapes){
            for(CollisionShape *collisionShape_Group2 : collisionGroups[std::get<1>(pair.collisionGroups)]->collisionShapes){
                if(pair.checkCollision(collisionShape_Group1, collisionShape_Group2)){
                    Collision collision;
                    collision.side = determineCollisionSide(collisionShape_Group1, collisionShape_Group2);
                    collision.from = collisionShape_Group1; // ! Assuming CS1 is always 'from' (moveable)
                    collision.with = collisionShape_Group2;

                    collisions.push_back(collision);
                }
            }

            // Run responses
            // TODO check if any collisionResponses exist (print message?)
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