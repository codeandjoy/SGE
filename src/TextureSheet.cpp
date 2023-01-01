#include "TextureSheet.h"

TextureSheet::TextureSheet(int textureSizeX, int textureSizeY, int numTexturesX, int numTexturesY, std::string textureSheetLocation){
    this->textureSheetLocation = textureSheetLocation;
    textureSheet.loadFromFile(textureSheetLocation);

    // Create coordinates vector
    for(int i = 0; i < numTexturesY*textureSizeY; i += textureSizeY){
        for(int j = 0; j < numTexturesX*textureSizeX; j += textureSizeX){
            textureRects.push_back(sf::IntRect(j, i, textureSizeX, textureSizeY));
        }
    }
}

sf::Texture* TextureSheet::getTextureSheet(){
    return &textureSheet;
}

sf::IntRect TextureSheet::getTextureRect(int textureN){
    return textureRects[textureN];
}