#include "Spritesheet.h"

Spritesheet::Spritesheet(int textureSizeX, int textureSizeY, int numTexturesX, int numTexturesY, std::string spritesheetLocation){
    spritesheet.loadFromFile(spritesheetLocation);

    // Create coordinates vector
    for(int i = 0; i < numTexturesY*textureSizeY; i += textureSizeY){
        for(int j = 0; j < numTexturesX*textureSizeX; j += textureSizeX){
            textureRects.push_back(sf::IntRect(j, i, textureSizeX, textureSizeY));
        }
    }
}

sf::Texture* Spritesheet::getSpritesheet(){
    return &spritesheet;
}

sf::IntRect Spritesheet::getTextureRect(int textureN){
    return textureRects[textureN];
}