#include "PhysicalObject.h"


sf::Sprite* sge::PhysicalObject::getOwnerSprite(){ return m_ownerSpritePtr; }

void sge::PhysicalObject::addComputationScript(std::string name, std::function<void(sge::PhysicalObject*, float)> computation){
    m_computationScripts[name] = computation;
    m_computationScriptsOrder.push_back(name);
}

void sge::PhysicalObject::update(float dt){
    for(std::string computation : m_computationScriptsOrder){
        m_computationScripts[computation](this, dt);
    }
};