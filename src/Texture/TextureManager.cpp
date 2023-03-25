#include "TextureManager.h"

// * Textures
void TextureManager::loadTexture(std::string location, std::string name, TextureSheetSizes textureSheetSizes){ loadedTextures[name] = new TextureSheet(textureSheetSizes, location); }
TextureSheet* TextureManager::getTexture(std::string name){ return loadedTextures[name]; }
// *

// * Animations
void TextureManager::addAnimation(std::string name, Animation* animation){ animations[name] = animation; }
Animation* TextureManager::getAnimation(std::string name){ return animations[name]; }
void TextureManager::deleteAnimation(std::string name){ animations.erase(name); }
// *

void TextureManager::initAnimationClocks(){
    for(auto& [key, animation] : animations){
        animation->restartClock();
    }
}

void TextureManager::updateAnimations(){
    for(auto& [key, animation] : animations){
        animation->run();
    }
}