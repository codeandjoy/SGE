#include "AnimationManager.h"
#include "Animation.h"


void sge::AnimationManager::update(float dt){
    for(sge::Animation* animation : m_components){
        if(animation->isActive) animation->runForward();
    }
}