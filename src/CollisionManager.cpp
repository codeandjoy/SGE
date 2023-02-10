#include "CollisionManager.h"
#include "Collision.h"
#include "CollisionUtils.h"

void CollisionManager::createCollisionGroup(std::string name, CollisionGroupType type, std::vector<PhysicalObject*> physicalObjectVec){
    // TODO check if already exists (has length)
    collisionGroups[name] = CollisionGroup {type, physicalObjectVec};
}

void CollisionManager::createCollisionPair(std::string name, std::string group1, std::string group2){
    // TODO Check if both groups exist in collisionGroups
    collisionPairs[name] = CollisionPair{std::make_tuple(group1, group2)};
}

void CollisionManager::addCollisionResponse(std::string collisionPairName, const std::function<void(std::vector<Collision>)> &response){
    collisionPairs[collisionPairName].collisionResponses.push_back(response);
}

void CollisionManager::setCollisionDetectionAlgorithm(std::string collisionPairName, const std::function<bool(PhysicalObject *PO1, PhysicalObject *PO2)> &cda){
    collisionPairs[collisionPairName].checkCollision = cda;
}

void CollisionManager::updateCollisions(){
    // TODO check if any collision pairs are added

    std::vector<Collision> collisions;

    // TODO refactor ?
    for(auto const& [name, pair] : collisionPairs){
        // Determine all collisions
        for(PhysicalObject *physicalObjectCG1 : collisionGroups[std::get<0>(pair.collisionGroups)].physicalObjects){
            for(PhysicalObject *physicalObjectCG2 : collisionGroups[std::get<1>(pair.collisionGroups)].physicalObjects){
                if(pair.checkCollision(physicalObjectCG1, physicalObjectCG2)){
                    Collision collision;
                    collision.side = determineSide(physicalObjectCG1, physicalObjectCG2);
                    collision.from = physicalObjectCG1;
                    collision.with = physicalObjectCG2;

                    collisions.push_back(collision);
                }
            }

            // Run responses
            // TODO check if any collisionResponses exist (print message?)
            for(std::function collisionResponse : pair.collisionResponses){
                collisionResponse(collisions);
            }

            // Reset
            collisions.clear();
        }
    }
}