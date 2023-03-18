#include "PhysicalObject.h"
#include "../utils/approach.h"

// * Utils
PhysicalObjectPositionData PhysicalObject::getPositionData(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}
// *


// * Movement
void PhysicalObject::setMovementVector(sf::Vector2f _movementVector){ movementVector = _movementVector; }
void PhysicalObject::setMovementVectorX(float x){ movementVector = sf::Vector2f(x, movementVector.y); }
void PhysicalObject::setMovementVectorY(float y){ movementVector = sf::Vector2f(movementVector.x, y); }
sf::Vector2f PhysicalObject::getMovementVector(){ return movementVector; }

void PhysicalObject::setVelocityGoal(sf::Vector2f goal){ velocityGoal = goal; }
void PhysicalObject::setVelocityGoalX(float goalX){ velocityGoal.x = goalX; }
void PhysicalObject::setVelocityGoalY(float goalY){ velocityGoal.y = goalY; }

void PhysicalObject::movementStop(){ movementVector = sf::Vector2f(0, 0);  };
void PhysicalObject::movementStopX(){ movementVector = sf::Vector2f(0, movementVector.y); };
void PhysicalObject::movementStopY(){ movementVector = sf::Vector2f(movementVector.x, 0); };
// *


// * Actions
void PhysicalObject::createAction(std::string _name, std::function<void()> _action){ actions[_name] = _action; }

void PhysicalObject::doAction(std::string actionName){
    if(!actions.count(actionName)){
        printf("Action '%s' does not exist\n", actionName.c_str());
        return;
    }

    actions[actionName]();
}

void PhysicalObject::createContinuousAction(std::string _name, std::function<void(float dt)> _action){ continuousActions[_name] = { false, _action }; }
void PhysicalObject::runContinuousAction(std::string continousActionName){ continuousActions[continousActionName].shouldRun = true; }
void PhysicalObject::stopContinuousAction(std::string continousActionName){ continuousActions[continousActionName].shouldRun = false; }
// *


// * Physical properties
void PhysicalObject::setMass(float _mass){ mass = _mass; }
float PhysicalObject::getMass(){ return mass; }

void PhysicalObject::setIsFlying(bool is){ isFlying = is; }
bool PhysicalObject::getIsFlying(){ return isFlying ;}
// *


void PhysicalObject::update(float dt){
    // ? Movement is a ContinuousAction ? 
    movementVector.x = approach(velocityGoal.x, movementVector.x, dt*5000);
    movementVector.y = approach(velocityGoal.y, movementVector.y, dt*5000);
    setPosition(getPosition() + movementVector * dt);

    for(auto const& [name, continuousAction] : continuousActions){
        if(continuousAction.shouldRun) continuousAction.runAction(dt);
    }
};