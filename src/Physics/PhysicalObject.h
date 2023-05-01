#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>


namespace sge{
    class PhysicalObject{
        public:
            PhysicalObject(sf::Sprite* ownerSprite);

            
            sf::Sprite* getOwnerSprite();


            sf::Vector2f velocity = sf::Vector2f(0, 0);
            sf::Vector2f acceleration = sf::Vector2f(0, 0);


            void createAction(std::string name, std::function<void()> action);
            void doAction(std::string name);


            void createContinuousComputation(std::string name, std::function<void(sge::PhysicalObject*, float)> computation);


            void createFlag(std::string name);
            bool getFlag(std::string flagName);
            void setFlag(std::string flagName, bool value);        


            void update(float dt);

        private:
            sf::Sprite* m_ownerSpritePtr;

            std::unordered_map<std::string, std::function<void()>> m_actions;
            std::unordered_map<std::string, std::function<void(sge::PhysicalObject*, float)>> m_continuousComputations;
            std::vector<std::string> m_continuousComputationOrder;
            std::unordered_map<std::string, bool> m_flags;
    };
}


#endif