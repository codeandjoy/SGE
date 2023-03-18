#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <SFML/Graphics.hpp>
#include "PhysicalObjectPositionData.h"
#include "ContinuousAction.h"
#include "ConditionalAction.h"


class PhysicalObject : public sf::Sprite{
    public:
        // * Utils
        PhysicalObjectPositionData getPositionData();
        // *


        // * Movement
        void setMovementVector(sf::Vector2f _movementVector); // ? Use movement methods in the future?
        void setMovementVectorX(float x); // ? Use movement methods in the future?
        void setMovementVectorY(float y); // ? Use movement methods in the future?
        sf::Vector2f getMovementVector();

        void setVelocityGoal(sf::Vector2f goal);
        void setVelocityGoalX(float goalX);
        void setVelocityGoalY(float goalY);
        
        void movementStop();
        void movementStopX();
        void movementStopY();
        // void movementAccelerate();
        // void movementSlacken();
        // ? void setVelocityCap(...) (sets max possible velocity vector values)
        // ? setMovementFunction(lambda) (sets movement algorithm (e.g. acceleration -> keeping velocity -> slowing down -> stop))
        // *


        // * Actions
        void createAction(std::string _name, std::function<void()> _action);
        void doAction(std::string actionName);

        void createContinuousAction(std::string _name, std::function<void(float dt)> _action);
        void runContinuousAction(std::string continuousActonName);
        void stopContinuousAction(std::string continuousActonName);
        
        void createConditionalAction(std::string _name, std::function<bool()> _condition, std::function<void()> _action);
        // removeConditionalAction(...)
        // *


        // * Physical properties
        void setMass(float _mass);
        float getMass();
        
        void setIsFlying(bool is); // ? Use just mass = 0 to 'fly' ?
        bool getIsFlying();
        // *
        

        void update(float dt);

    private:
        sf::Vector2f movementVector = sf::Vector2f(0, 0);
        sf::Vector2f velocityGoal;

        std::map<std::string, std::function<void()>> actions;
        std::map<std::string, ContinuousAction> continuousActions;
        std::map<std::string, ConditionalAction> conditionalActions;
        
        float mass = 0;
        bool isFlying = false;
};


#endif