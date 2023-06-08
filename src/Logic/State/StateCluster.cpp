#include <algorithm>

#include "StateCluster.h"
#include "State.h"


std::vector<sge::State*> sge::StateCluster::getActiveStates(){
    std::vector<sge::State*> activeStates;

    for(std::string activeStateName : m_activeStates){
        activeStates.push_back(states[activeStateName]);
    }

    return activeStates;
}
std::vector<std::string> sge::StateCluster::getActiveStateNames(){ return m_activeStates; }


void sge::StateCluster::activateState(std::string name){
    if(!isStateActive(name)){
        states[name]->enterScript();
        m_activeStates.push_back(name);
    }
}
void sge::StateCluster::deactivateState(std::string name){
    if(isStateActive(name)){
        states[name]->exitScript();
        m_activeStates.erase(std::remove(m_activeStates.begin(), m_activeStates.end(), name), m_activeStates.end());
    }
}


bool sge::StateCluster::isStateActive(std::string name){
    return std::count(m_activeStates.begin(), m_activeStates.end(), name);
}