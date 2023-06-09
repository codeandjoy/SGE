#ifndef COMPUTATION_SCRIPTS_H
#define COMPUTATION_SCRIPTS_H

#include <SFML/Graphics.hpp>
#include <functional>


namespace sge{
    class MotionUnit;

    std::function<void(sge::MotionUnit*, float)> updatePositionBasedOnVelocity();

    std::function<void(sge::MotionUnit*, float)> updateVelocityBasedOnAcceleration(sf::Vector2f speedLimit=sf::Vector2f(9999, 9999));
}


#endif