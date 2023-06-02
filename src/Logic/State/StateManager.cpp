#include <algorithm>

#include "StateManager.h"
#include "StateCluster.h"
#include "State.h"


void sge::StateManager::update(float dt){
    for(StateCluster* stateCluster : m_components){
        stateCluster->getCurrentState()->updateScript(dt, stateCluster);
    }
}