#include "ComputationScripts.h"
#include "MotionUnit.h"
#include "../../utils/Approach.h"


// displacement = v * Δt
// new position = old position + displacement
std::function<void(sge::MotionUnit*, float)> sge::updatePositionBasedOnVelocity(){
    return [](sge::MotionUnit* thisMotionUnit, float dt){
        thisMotionUnit->getOwnerSprite()->setPosition(thisMotionUnit->getOwnerSprite()->getPosition() + thisMotionUnit->velocity * dt);
    };
}

// Δv = a / Δt
std::function<void(sge::MotionUnit*, float)> sge::updateVelocityBasedOnAcceleration(sf::Vector2f speedLimit){
    return [speedLimit](sge::MotionUnit* thisMotionUnit, float dt){
        thisMotionUnit->velocity.x = sge::approach(speedLimit.x, thisMotionUnit->acceleration.x*dt, thisMotionUnit->velocity.x);
        thisMotionUnit->velocity.y = sge::approach(speedLimit.y, thisMotionUnit->acceleration.y*dt, thisMotionUnit->velocity.y);
    };
}

// a = Σ contactForces + Σ fieldForces
std::function<void(sge::MotionUnit*, float)> sge::calculateAcceleration(){
    return [](sge::MotionUnit* thisMotionUnit, float dt){
        sf::Vector2f netForce = sf::Vector2f(0, 0);
        for(auto& [_, force] : thisMotionUnit->contactForces){
            netForce += force;
        }
        for(auto& [_, force] : thisMotionUnit->fieldForces){
            netForce += force;
        }

        thisMotionUnit->acceleration = netForce;
    };
}