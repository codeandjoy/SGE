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


        void createAction(std::string name, std::function<void()> action);
        void doAction(std::string name);
        // removeAction()


        void createContinuousAction(std::string name, std::function<void(float dt)> action);
        void runContinuousAction(std::string name);
        void stopContinuousAction(std::string name);
        // removeContinuousAction()
        

        void createConditionalAction(std::string name, std::function<bool()> condition, std::function<void()> action);
        // removeConditionalAction()


        void createFlag(std::string name);
        bool getFlag(std::string flagName);
        void setFlag(std::string flagName, bool value);        
        // removeflag()


        void update(float dt);

    private:
        std::map<std::string, std::function<void()>> m_actions;
        std::map<std::string, ContinuousAction> m_continuousActions;
        std::map<std::string, ConditionalAction> m_conditionalActions;
        std::map<std::string, bool> m_flags;
};


#endif