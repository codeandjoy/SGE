#include "TextureSheet.h"


TextureSheet::TextureSheet(TextureSheetSizes textureSheetSizes, std::string location){
    m_location = location;
    m_textureSheet.loadFromFile(location);

    for(int i = 0; i < textureSheetSizes.numTexturesY*textureSheetSizes.textureSizeY; i += textureSheetSizes.textureSizeY){
        for(int j = 0; j < textureSheetSizes.numTexturesX*textureSheetSizes.textureSizeX; j += textureSheetSizes.textureSizeX){
            m_textureRects.push_back(sf::IntRect(j, i, textureSheetSizes.textureSizeX, textureSheetSizes.textureSizeY));
        }
    }
}



std::string TextureSheet::getLocation(){ return m_location; }
sf::Texture* TextureSheet::getTextureSheet(){ return &m_textureSheet; }
sf::IntRect TextureSheet::getTextureRect(int textureN){ return m_textureRects[textureN]; }