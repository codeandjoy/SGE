#ifndef MOTION_UNIT_H
#define MOTION_UNIT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include "../../Component/StatefulComponent.h"


namespace sge{
    class MotionUnit : public sge::StatefulComponent{
        public:
            MotionUnit(sf::Sprite* ownerSprite) : m_ownerSpritePtr(ownerSprite){};

            sf::Sprite* getOwnerSprite();


            sf::Vector2f velocity = sf::Vector2f(0, 0);
            sf::Vector2f acceleration = sf::Vector2f(0, 0);
            std::unordered_map<std::string, sf::Vector2f> extraProperties;


            std::unordered_map<std::string, sf::Vector2f> contactForces; // frictional forces, air resistance, tension, applied forces, normal forces, forces in springs
            std::unordered_map<std::string, sf::Vector2f> fieldForces; // gravitational, electric, magnetic


            void addComputationScript(std::string name, std::function<void(sge::MotionUnit*, float)> computation);

            void update(float dt);

        private:
            sf::Sprite* m_ownerSpritePtr;

            std::unordered_map<std::string, std::function<void(sge::MotionUnit*, float)>> m_computationScripts;
            std::vector<std::string> m_computationScriptsOrder;
    };
}


#endif