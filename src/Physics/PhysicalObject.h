#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <SFML/Graphics.hpp>
#include "ContinuousComputation.h"


class PhysicalObject : public sf::Sprite{
    public:
        sf::Vector2f velocity = sf::Vector2f(0, 0);
        sf::Vector2f acceleration = sf::Vector2f(0, 0);
        sf::Vector2f speedLimit = sf::Vector2f(9999,9999);


        void createAction(std::string name, std::function<void()> action);
        void doAction(std::string name);
        // removeAction()


        void createContinuousComputation(std::string name, std::function<void(float dt)> computation);
        void runContinuousComputation(std::string name);
        void stopContinuousComputation(std::string name);
        

        void createFlag(std::string name);
        bool getFlag(std::string flagName);
        void setFlag(std::string flagName, bool value);        
        // removeflag()


        void update(float dt);

    private:
        std::unordered_map<std::string, std::function<void()>> m_actions;
        std::unordered_map<std::string, ContinuousComputation> m_continuousComputations;
        std::vector<std::string> m_continuousComputationOrder;
        std::unordered_map<std::string, bool> m_flags;
};


#endif