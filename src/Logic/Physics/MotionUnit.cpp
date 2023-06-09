#include "MotionUnit.h"


sf::Sprite* sge::MotionUnit::getOwnerSprite(){ return m_ownerSpritePtr; }

void sge::MotionUnit::addComputationScript(std::string name, std::function<void(sge::MotionUnit*, float)> computation){
    m_computationScripts[name] = computation;
    m_computationScriptsOrder.push_back(name);
}

void sge::MotionUnit::update(float dt){
    for(std::string computation : m_computationScriptsOrder){
        m_computationScripts[computation](this, dt);
    }
};