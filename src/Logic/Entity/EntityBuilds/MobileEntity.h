#ifndef MOBILE_ENTITY_H
#define MOBILE_ENTITY_H

#include <SFML/Graphics.hpp>

#include "StaticEntity.h"
#include "../../Physics/MotionUnit.h"
#include "../../Physics/ComputationScripts.h"


namespace sge{
    class MobileEntity : public sge::StaticEntity{
        public:
            MobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups)
                : sge::StaticEntity(texture, textureRect, position, collisionGroups){
                    motionUnit = new MotionUnit(sprite);
                    motionUnit->addComputationScript("update_velocity", sge::updateVelocityBasedOnAcceleration());
                    motionUnit->addComputationScript("update_position", sge::updatePositionBasedOnVelocity());
                }
    };
}



#endif