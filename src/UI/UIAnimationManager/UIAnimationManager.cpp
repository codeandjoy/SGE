#include <algorithm>
#include "UIAnimationManager.h"
#include "../../Common/Animation/Animation.h"


void sge::UIAnimationManager::registerAnimation(sge::Animation* animation){ m_activeAnimations.push_back(animation); }
void sge::UIAnimationManager::deregisterAnimation(sge::Animation* animation){
    m_activeAnimations.erase(std::remove(m_activeAnimations.begin(), m_activeAnimations.end(), animation), m_activeAnimations.end());
    m_inactiveAnimations.erase(std::remove(m_inactiveAnimations.begin(), m_inactiveAnimations.end(), animation), m_inactiveAnimations.end());
}
std::vector<sge::Animation*> sge::UIAnimationManager::getAllActiveAnimations(){ return m_activeAnimations; }



void sge::UIAnimationManager::activateAnimation(sge::Animation* animation){
    deregisterAnimation(animation);
    m_activeAnimations.push_back(animation);
}
void sge::UIAnimationManager::deactivateAnimation(sge::Animation* animation){
    deregisterAnimation(animation);
    m_inactiveAnimations.push_back(animation);
}

void sge::UIAnimationManager::initAnimationClocks(){
    for(sge::Animation* animation : m_activeAnimations){
        animation->restartClock();
    }
}

void sge::UIAnimationManager::updateActiveAnimations(){
    for(sge::Animation* animation : m_activeAnimations){
        animation->run();
    }
}