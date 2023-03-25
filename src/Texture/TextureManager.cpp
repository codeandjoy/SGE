#include "TextureManager.h"

// * Textures
void TextureManager::loadTexture(std::string location, std::string name, TextureSheetSizes textureSheetSizes){ loadedTextures[name] = new TextureSheet(textureSheetSizes, location); }
TextureSheet* TextureManager::getTexture(std::string name){ return loadedTextures[name]; }
// *

// * Animations
void TextureManager::registerAnimation(Animation* animation){ animations.push_back(animation); }
void TextureManager::deregisterAnimation(Animation* animation){ animations.erase(std::remove(animations.begin(), animations.end(), animation), animations.end()); }
// *

void TextureManager::initAnimationClocks(){
    for(Animation* animation : animations){
        animation->restartClock();
    }
}

void TextureManager::updateAnimations(){
    for(Animation* animation : animations){
        animation->run();
    }
}