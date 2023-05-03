#include <algorithm>
#include "UIAnimationManager.h"


void sge::UIAnimationManager::registerAnimation(sge::Animation* animation){ m_activeAnimations.push_back(animation); }
void sge::UIAnimationManager::deregisterAnimation(sge::Animation* animation){
    m_activeAnimations.erase(std::remove(m_activeAnimations.begin(), m_activeAnimations.end(), animation), m_activeAnimations.end());
    m_inactiveAnimations.erase(std::remove(m_inactiveAnimations.begin(), m_inactiveAnimations.end(), animation), m_inactiveAnimations.end());
}



void sge::UIAnimationManager::activateAnimation(sge::Animation* animation){
    deregisterAnimation(animation);
    m_activeAnimations.push_back(animation);
}
void sge::UIAnimationManager::deactivateAnimation(sge::Animation* animation){
    deregisterAnimation(animation);
    m_inactiveAnimations.push_back(animation);
}