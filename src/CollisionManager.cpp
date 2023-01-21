#include "CollisionManager.h"

void CollisionManager::createCollisionGroup(std::string name, CollisionGroupType type, std::vector<PhysicalObject*> spriteVec){
    // TODO check if already exists (has length)
    collisionGroups[name] = CollisionGroup {type, spriteVec};
}

void CollisionManager::createCollisionPair(std::string name, std::string group1, std::string group2){
    // TODO Check if both groups exist in collisionGroups
    collisionPairs[name] = CollisionPair{std::make_tuple(group1, group2)};
}

void CollisionManager::addCollisionResponse(std::string collisionPairName, const std::function<void(sf::Sprite *sprite1, sf::Sprite *sprite2)> &response){
    collisionPairs[collisionPairName].collisionResponses.push_back(response);
}

void CollisionManager::updateCollisions(){
    // TODO check if any collision pairs are added

    for(auto const& [name, pair] : collisionPairs){
        // ! Hand coded bounding box collision detection
        // ? Expand with circle and pixel perfect
        // Check collision between each sprite in pairs of groups
        for(sf::Sprite *spriteCG0 : collisionGroups[std::get<0>(pair.collisionGroups)].spriteVec){
            for(sf::Sprite *spriteCG1 : collisionGroups[std::get<1>(pair.collisionGroups)].spriteVec){
                if(spriteCG0->getGlobalBounds().intersects(spriteCG1->getGlobalBounds())){
                    // TODO check if any collisionResponses exist (print message?)

                    for(std::function collisionResponse : pair.collisionResponses){
                        // ? passes 'informantion' structure to response with collision informantion (like side, depth etc.)
                        collisionResponse(spriteCG0, spriteCG1);
                    }
                }
            }
        }
    }
}