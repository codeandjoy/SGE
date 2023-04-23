#include "PhysicalObject.h"


void PhysicalObject::createAction(std::string name, std::function<void()> action){ m_actions[name] = action; }
void PhysicalObject::doAction(std::string name){ m_actions[name](); }



void PhysicalObject::createContinuousComputation(std::string name, std::function<void(PhysicalObject*, float)> computation){
    m_continuousComputations[name] = computation;
    m_continuousComputationOrder.push_back(name);
}



void PhysicalObject::createFlag(std::string name){ m_flags[name] = false; }
bool PhysicalObject::getFlag(std::string flagName){ return m_flags[flagName]; }
void PhysicalObject::setFlag(std::string flagName, bool value){ m_flags[flagName] = value; }



void PhysicalObject::update(float dt){
    // Run continuous computations in order of insertion
    for(std::string computation : m_continuousComputationOrder){
        m_continuousComputations[computation](this, dt);
    }
};