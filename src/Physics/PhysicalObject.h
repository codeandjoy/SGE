#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <SFML/Graphics.hpp>
#include "ContinuousAction.h"
#include "ConditionalAction.h"


class PhysicalObject : public sf::Sprite{
    public:
        sf::Vector2f velocity = sf::Vector2f(0, 0);
        sf::Vector2f acceleration = sf::Vector2f(0, 0);
        sf::Vector2f speedLimit = sf::Vector2f(9999,9999);


        // * Actions
        void createAction(std::string _name, std::function<void()> _action);
        void doAction(std::string actionName);

        void createContinuousAction(std::string _name, std::function<void(float dt)> _action);
        void runContinuousAction(std::string continuousActonName);
        void stopContinuousAction(std::string continuousActonName);
        
        void createConditionalAction(std::string _name, std::function<bool()> _condition, std::function<void()> _action);
        // removeConditionalAction(...)
        // *


        // * Flags
        void createFlag(std::string _name);
        bool getFlag(std::string flagName);
        void setFlag(std::string flagName, bool value);        
        // removeflag()
        // *


        void update(float dt);

    private:
        std::map<std::string, std::function<void()>> actions;
        std::map<std::string, ContinuousAction> continuousActions;
        std::map<std::string, ConditionalAction> conditionalActions;
        std::map<std::string, bool> flags;
};


#endif