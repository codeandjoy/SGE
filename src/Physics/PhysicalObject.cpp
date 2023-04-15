#include "PhysicalObject.h"


void PhysicalObject::createAction(std::string name, std::function<void()> action){ m_actions[name] = action; }
void PhysicalObject::doAction(std::string name){ m_actions[name](); }



void PhysicalObject::createContinuousComputation(std::string name, std::function<void(float dt)> computation){
    m_continuousComputations[name] = { true, computation };
    m_continuousComputationOrder.push_back(name);
}
void PhysicalObject::runContinuousComputation(std::string name){ m_continuousComputations[name].shouldRun = true; }
void PhysicalObject::stopContinuousComputation(std::string name){ m_continuousComputations[name].shouldRun = false; }



void PhysicalObject::createFlag(std::string name){ m_flags[name] = false; }
bool PhysicalObject::getFlag(std::string flagName){ return m_flags[flagName]; }
void PhysicalObject::setFlag(std::string flagName, bool value){ m_flags[flagName] = value; }



void PhysicalObject::update(float dt){
    for(std::string computation : m_continuousComputationOrder){
        if(m_continuousComputations[computation].shouldRun){
            m_continuousComputations[computation].compute(dt);
        }
    }
};