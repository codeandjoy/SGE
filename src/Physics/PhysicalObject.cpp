#include "PhysicalObject.h"


// * Actions
void PhysicalObject::createAction(std::string _name, std::function<void()> _action){ actions[_name] = _action; }

void PhysicalObject::doAction(std::string actionName){
    if(!actions.count(actionName)){
        printf("Action '%s' does not exist\n", actionName.c_str());
        return;
    }

    actions[actionName]();
}

void PhysicalObject::createContinuousAction(std::string _name, std::function<void(float dt)> _action){ continuousActions[_name] = { false, _action }; }
void PhysicalObject::runContinuousAction(std::string continousActionName){ continuousActions[continousActionName].shouldRun = true; }
void PhysicalObject::stopContinuousAction(std::string continousActionName){ continuousActions[continousActionName].shouldRun = false; }

void PhysicalObject::createConditionalAction(std::string _name, std::function<bool()> _condition, std::function<void()> _action){ conditionalActions[_name] = { _condition, _action }; }
// *


// * Flags
// ! check if flags exist before returning
void PhysicalObject::createFlag(std::string _name){ flags[_name] = false; }
bool PhysicalObject::getFlag(std::string flagName){ return flags[flagName]; }
void PhysicalObject::setFlag(std::string flagName, bool value){ flags[flagName] = value; }
//*


void PhysicalObject::update(float dt){
    for(auto const& [name, continuousAction] : continuousActions){
        if(continuousAction.shouldRun) continuousAction.runAction(dt);
    }

    for(auto const& [name, conditionalAction] : conditionalActions){
        if(conditionalAction.condition()){
            conditionalAction.runAction();
        }
    }

    setPosition(getPosition() + velocity * dt);
};