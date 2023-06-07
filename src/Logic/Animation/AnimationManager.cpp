#include "AnimationManager.h"
#include "AnimationCluster.h"


void sge::AnimationManager::update(float dt){
    for(sge::AnimationCluster* animation : m_components){
        if(animation->isActive) animation->run();
    }
}