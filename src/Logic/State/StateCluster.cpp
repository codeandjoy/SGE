#include "StateCluster.h"
#include "State.h"


sge::State* sge::StateCluster::getCurrentState(){ return states[m_currentState]; }
std::string sge::StateCluster::getCurrentStateName(){ return m_currentState; }
void sge::StateCluster::setCurrentState(std::string name){
    if(m_currentState != ""){
        states[m_currentState]->exitScript();
    }
    states[name]->enterScript();

    m_currentState = name;
}