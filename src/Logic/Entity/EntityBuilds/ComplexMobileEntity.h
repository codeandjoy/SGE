#ifndef COMPLEX_MOBILE_ENTITY_H
#define COMPLEX_MOBILE_ENTITY_H

#include <SFML/Graphics.hpp>

#include "MobileEntity.h"
#include "../../Physics/MotionUnit.h"
#include "../../Physics/ComputationScripts.h"


namespace sge{
    class ComplexMobileEntity : public sge::StaticEntity{
        public:
            ComplexMobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups)
                : sge::StaticEntity(texture, textureRect, position, collisionGroups){
                    motionUnit->addComputationScript("update_acceleration", sge::calculateAcceleration());
                    motionUnit->addComputationScript("update_velocity", sge::updateVelocityBasedOnAcceleration());
                    motionUnit->addComputationScript("update_position", sge::updatePositionBasedOnVelocity());
                }
    };
}



#endif