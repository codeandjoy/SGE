#include "AnimationManager.h"
#include "Animation.h"


void sge::AnimationManager::registerAnimation(sge::Animation* animation){ m_animations.push_back(animation); }
void sge::AnimationManager::deregisterAnimation(sge::Animation* animation){ m_animations.erase(std::remove(m_animations.begin(), m_animations.end(), animation), m_animations.end()); }
void sge::AnimationManager::deregisterAllAnimations(){ m_animations.clear(); }


void sge::AnimationManager::initAnimationClocks(){
    for(sge::Animation* animation : m_animations){
        animation->restartClock();
    }
}

void sge::AnimationManager::updateAnimations(){
    for(sge::Animation* animation : m_animations){
        animation->run();
    }
}