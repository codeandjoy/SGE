#ifndef SIMPLE_MOBILE_ENTITY_H
#define SIMPLE_MOBILE_ENTITY_H

#include <SFML/Graphics.hpp>

#include "MobileEntity.h"
#include "../../Physics/MotionUnit.h"
#include "../../Physics/ComputationScripts.h"


namespace sge{
    class SimpleMobileEntity : public sge::MobileEntity{
        public:
            SimpleMobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups)
                : sge::MobileEntity(texture, textureRect, position, collisionGroups){
                    motionUnit->addComputationScript("update_velocity", sge::updateVelocityBasedOnAcceleration());
                    motionUnit->addComputationScript("update_position", sge::updatePositionBasedOnVelocity());
                }
    };
}



#endif