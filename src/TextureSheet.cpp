#include "TextureSheet.h"

TextureSheet::TextureSheet(TextureSheetSizes tss, std::string location){
    this->location = location;
    textureSheet.loadFromFile(location);

    // Create coordinates vector
    for(int i = 0; i < tss.numTexturesY*tss.textureSizeY; i += tss.textureSizeY){
        for(int j = 0; j < tss.numTexturesX*tss.textureSizeX; j += tss.textureSizeX){
            textureRects.push_back(sf::IntRect(j, i, tss.textureSizeX, tss.textureSizeY));
        }
    }
}

std::string TextureSheet::getLocation(){
    return location;
}

sf::Texture* TextureSheet::getTextureSheet(){
    return &textureSheet;
}

sf::IntRect TextureSheet::getTextureRect(int textureN){
    return textureRects[textureN];
}