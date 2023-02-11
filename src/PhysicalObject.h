#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <SFML/Graphics.hpp>
#include "PhysicalObjectPositionData.h"
#include "ContinuousAction.h"


class PhysicalObject : public sf::Sprite{
    public:
    PhysicalObjectPositionData getPositionData();
    
    void setMovementVector(sf::Vector2f _movementVector); // ? Use movement methods in the future?
    void setMovementVectorX(float x); // ? Use movement methods in the future?
    void setMovementVectorY(float y); // ? Use movement methods in the future?
    sf::Vector2f getMovementVector();

    void setVelocityGoal(sf::Vector2f goal);
    void setVelocityGoalX(float goalX);
    void setVelocityGoalY(float goalY);

    void createAction(std::string _name, std::function<void()> _action);
    void doAction(std::string actionName);

    void createContinuousAction(std::string _name, std::function<void(float dt)> _action);
    void runContinuousAction(std::string continuousActonName);
    void stopContinuousAction(std::string continuousActonName);

    void setMass(float _mass);
    float getMass();
    
    void setIsFlying(bool is); // ? Use just mass = 0 to 'fly' ?
    bool getIsFlying();

    // void movementAccelerate();
    // void movementSlacken();
    void movementStop();
    void movementStopX();
    void movementStopY();
    // ? void setVelocityCap(...) (sets max possible velocity vector values)
    // ? setMovementFunction(lambda) (sets movement algorithm (e.g. acceleration -> keeping velocity -> slowing down -> stop))
    void update(float dt);

    private:
    sf::Vector2f movementVector = sf::Vector2f(0, 0);
    sf::Vector2f velocityGoal;

    std::map<std::string, std::function<void()>> actions;
    std::map<std::string, ContinuousAction> continuousActions;
    
    float mass = 0;
    bool isFlying = false;
};


#endif