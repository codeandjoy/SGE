#include "CollisionManager.h"

void CollisionManager::createCollisionGroup(std::string name, CollisionGroupType type, std::vector<PhysicalObject*> physicalObjectVec){
    // TODO check if already exists (has length)
    collisionGroups[name] = CollisionGroup {type, physicalObjectVec};
}

void CollisionManager::createCollisionPair(std::string name, std::string group1, std::string group2){
    // TODO Check if both groups exist in collisionGroups
    collisionPairs[name] = CollisionPair{std::make_tuple(group1, group2)};
}

void CollisionManager::addCollisionResponse(std::string collisionPairName, const std::function<void(PhysicalObject *physicalObject1, PhysicalObject *physicalObject2)> &response){
    collisionPairs[collisionPairName].collisionResponses.push_back(response);
}

void CollisionManager::setCollisionDetectionAlgorithm(std::string collisionPairName, const std::function<bool(PhysicalObject *PO1, PhysicalObject *PO2)> &cda){
    collisionPairs[collisionPairName].checkCollision = cda;
}

void CollisionManager::updateCollisions(){
    // TODO check if any collision pairs are added

    for(auto const& [name, pair] : collisionPairs){
        // ! Hand coded bounding box collision detection
        // ? Expand with circle and pixel perfect
        // Check collision between each sprite in pairs of groups
        for(PhysicalObject *physicalObjectCG1 : collisionGroups[std::get<0>(pair.collisionGroups)].physicalObjects){
            for(PhysicalObject *physicalObjectCG2 : collisionGroups[std::get<1>(pair.collisionGroups)].physicalObjects){
                if(pair.checkCollision(physicalObjectCG1, physicalObjectCG2)){
                    // TODO check if any collisionResponses exist (print message?)

                    for(std::function collisionResponse : pair.collisionResponses){
                        // ? passes 'informantion' structure to response with collision informantion (like side, depth etc.)
                        collisionResponse(physicalObjectCG1, physicalObjectCG2);
                    }
                }
            }
        }
    }
}