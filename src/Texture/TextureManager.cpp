#include "TextureManager.h"
#include "TextureSheet.h"
#include "Animation.h"


void sge::TextureManager::loadTexture(std::string location, std::string name, sge::TextureSheetSizes textureSheetSizes){ m_loadedTextures[name] = new sge::TextureSheet(textureSheetSizes, location); }
sge::TextureSheet* sge::TextureManager::getTexture(std::string name){ return m_loadedTextures[name]; }


void sge::TextureManager::registerAnimation(sge::Animation* animation){ m_animations.push_back(animation); }
void sge::TextureManager::deregisterAnimation(sge::Animation* animation){ m_animations.erase(std::remove(m_animations.begin(), m_animations.end(), animation), m_animations.end()); }


void sge::TextureManager::initAnimationClocks(){
    for(sge::Animation* animation : m_animations){
        animation->restartClock();
    }
}

void sge::TextureManager::updateAnimations(){
    for(sge::Animation* animation : m_animations){
        animation->run();
    }
}