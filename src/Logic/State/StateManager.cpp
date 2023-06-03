#include <algorithm>

#include "StateManager.h"
#include "StateCluster.h"
#include "State.h"


void sge::StateManager::update(float dt){
    for(StateCluster* stateCluster : m_components){
        if(stateCluster->isActive) stateCluster->getCurrentState()->updateScript(dt, stateCluster);
    }
}