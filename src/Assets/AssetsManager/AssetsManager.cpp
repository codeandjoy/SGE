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


void sge::AssetsManager::loadSFX(std::string location, std::string name){
    sf::SoundBuffer* buffer = new sf::SoundBuffer();
    buffer->loadFromFile(location);

    sf::Sound* sound = new sf::Sound(*buffer);
    m_sfx[name] = std::make_pair(buffer, sound);
}
sf::Sound* sge::AssetsManager::getSound(std::string name){ return m_sfx[name].second; }


void sge::AssetsManager::specifyMusicLocation(std::string location, std::string name){ m_musicLocations[name] = location; }
std::string sge::AssetsManager::getMusicLocation(std::string name){ return m_musicLocations[name]; }