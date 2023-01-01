#include "TextureManager.h"

void TextureManager::load(std::string textureLocation, TextureSheetSizes textureSheetSizes, std::string textureName){
    if(loadedTextures.count(textureName)){
        printf("Can't load already existing texture '%s'\n", textureName.c_str());
        exit(1);
    }

    // TextureSheet ts(textureSheetSizes, textureLocation);
    loadedTextures[textureName] = new TextureSheet(textureSheetSizes, textureLocation);
}

bool TextureManager::isLoaded(std::string textureLocation){
    for(auto &[key, textureSheet] : loadedTextures){
        if(textureSheet->getLocation() == textureLocation) return true;
    }

    return false;
}

TextureSheet* TextureManager::get(std::string textureName){
    return loadedTextures[textureName];
}