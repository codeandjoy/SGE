#include "PhysicalObject.h"


void PhysicalObject::createAction(std::string name, std::function<void()> action){ m_actions[name] = action; }
void PhysicalObject::doAction(std::string name){ m_actions[name](); }



void PhysicalObject::createContinuousAction(std::string name, std::function<void(float dt)> action){ m_continuousActions[name] = { false, action }; }
void PhysicalObject::runContinuousAction(std::string name){ m_continuousActions[name].shouldRun = true; }
void PhysicalObject::stopContinuousAction(std::string name){ m_continuousActions[name].shouldRun = false; }



void PhysicalObject::createConditionalAction(std::string name, std::function<bool()> condition, std::function<void()> action){ m_conditionalActions[name] = { condition, action }; }



void PhysicalObject::createFlag(std::string name){ m_flags[name] = false; }
bool PhysicalObject::getFlag(std::string flagName){ return m_flags[flagName]; }
void PhysicalObject::setFlag(std::string flagName, bool value){ m_flags[flagName] = value; }



void PhysicalObject::update(float dt){
    for(auto const& [name, continuousAction] : m_continuousActions){
        if(continuousAction.shouldRun) continuousAction.runAction(dt);
    }

    for(auto const& [name, conditionalAction] : m_conditionalActions){
        if(conditionalAction.condition()){
            conditionalAction.runAction();
        }
    }

    setPosition(getPosition() + velocity * dt); // ? make part of default continuousActions, remove from here ?
};