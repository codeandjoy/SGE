#include "TextureSheet.h"


sge::TextureSheet::TextureSheet(sge::TextureSheetSizes textureSheetSizes, std::string location){
    m_location = location;
    m_textureSheet.loadFromFile(location);

    for(int i = 0; i < textureSheetSizes.numTexturesY*textureSheetSizes.textureSizeY; i += textureSheetSizes.textureSizeY+textureSheetSizes.gapY){
        for(int j = 0; j < textureSheetSizes.numTexturesX*textureSheetSizes.textureSizeX; j += textureSheetSizes.textureSizeX+textureSheetSizes.gapX){
            m_textureRects.push_back(sf::IntRect(j, i, textureSheetSizes.textureSizeX, textureSheetSizes.textureSizeY));
        }
    }
}



std::string sge::TextureSheet::getLocation(){ return m_location; }
sf::Texture* sge::TextureSheet::getTexture(){ return &m_textureSheet; }
sf::IntRect sge::TextureSheet::getTextureRect(int textureN){ return m_textureRects[textureN]; }