#ifndef CUSTOM_ENTITIES_H
#define CUSTOM_ENTITIES_H

#include "../../SGE.hpp"
#include "PlayerStates.h"


class GravityEntity : public sge::ComplexMobileEntity{
    public :
        GravityEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups)
            : sge::ComplexMobileEntity(texture, textureRect, position, collisionGroups){
                motionUnit->fieldForces["gravity"] = sf::Vector2f(0, 1000);
        }
};

class PlayerEntity : public GravityEntity{
    public:
        PlayerEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups, sge::TextureSheet* animationTextureSheet)
            : GravityEntity(texture, textureRect, position, collisionGroups){
                animationCluster = new sge::AnimationCluster(sprite);
                animationCluster->animationDelayMilliseconds = 80;
                animationCluster->addTextureSequence("idle", new sge::TextureSequence(std::vector<int>{260}, animationTextureSheet));
                animationCluster->addTextureSequence("in_air", new sge::TextureSequence(std::vector<int>{265}, animationTextureSheet));
                animationCluster->addTextureSequence("walking_right", new sge::TextureSequence(std::vector<int>{262, 263, 264}, animationTextureSheet));
                animationCluster->addTextureSequence("walking_left", new sge::TextureSequence(std::vector<int>{262, 263, 264}, animationTextureSheet, true));
                animationCluster->setCurrentTextureSequence("idle");

                collisionShapes["global_bounds"]->setSize(sf::Vector2f(16, 8));
                collisionShapes["global_bounds"]->offset = sf::Vector2f(0, 8);

                stateCluster = new sge::StateCluster();
                stateCluster->states["on_ground"] = new PlayerOnGroundState(this);
                stateCluster->states["jump"] = new PlayerJumpState(this);
                stateCluster->states["moving_right"] = new PlayerMovingRightState(this);
                stateCluster->states["moving_left"] = new PlayerMovingLeftState(this);
                stateCluster->activateState("jump"); // jump because player is initially falling
            }
};


#endif