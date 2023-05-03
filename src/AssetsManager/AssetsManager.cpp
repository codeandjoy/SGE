#include "AssetsManager.h"
#include "../Texture/TextureSheet.h"


void sge::AssetsManager::loadTextureSheet(std::string location, std::string name, sge::TextureSheetSizes textureSheetSizes){ m_textures[name] = new sge::TextureSheet(textureSheetSizes, location); }
sge::TextureSheet* sge::AssetsManager::getTextureSheet(std::string name){ return m_textures[name]; }

void sge::AssetsManager::loadFont(std::string location, std::string name){
    sf::Font* font = new sf::Font;
    font->loadFromFile(location);

    m_fonts[name] = font;
}
sf::Font* sge::AssetsManager::getFont(std::string name){ return m_fonts[name]; }