#include <algorithm>

#include "StateManager.h"
#include "StateCluster.h"
#include "State.h"


void sge::StateManager::registerStateCluster(sge::StateCluster* stateCluster){ m_stateClusters.push_back(stateCluster); }
void sge::StateManager::deregisterStateCluster(sge::StateCluster* stateCluster){
    m_stateClusters.erase(std::remove(m_stateClusters.begin(), m_stateClusters.end(), stateCluster), m_stateClusters.end());
}


void sge::StateManager::runUpdateScripts(float dt){
    for(StateCluster* stateCluster : m_stateClusters){
        stateCluster->getCurrentState()->updateScript(dt);
    }
}