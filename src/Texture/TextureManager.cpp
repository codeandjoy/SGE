#include "TextureManager.h"
#include "TextureSheet.h"
#include "Animation.h"


void TextureManager::loadTexture(std::string location, std::string name, TextureSheetSizes textureSheetSizes){ m_loadedTextures[name] = new TextureSheet(textureSheetSizes, location); }
TextureSheet* TextureManager::getTexture(std::string name){ return m_loadedTextures[name]; }


void TextureManager::registerAnimation(Animation* animation){ m_animations.push_back(animation); }
void TextureManager::deregisterAnimation(Animation* animation){ m_animations.erase(std::remove(m_animations.begin(), m_animations.end(), animation), m_animations.end()); }


void TextureManager::initAnimationClocks(){
    for(Animation* animation : m_animations){
        animation->restartClock();
    }
}

void TextureManager::updateAnimations(){
    for(Animation* animation : m_animations){
        animation->run();
    }
}