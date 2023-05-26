#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include <unordered_map>
#include <string>
#include <utility>
#include <SFML/Audio.hpp>

#include "../Texture/TextureSheetSizes.h"


namespace sge{
    class TextureSheet;

    class AssetsManager{
        public:
            void loadTextureSheet(std::string location, std::string name, sge::TextureSheetSizes textureSheetSizes);
            sge::TextureSheet* getTextureSheet(std::string name);

            void loadFont(std::string location, std::string name);
            sf::Font* getFont(std::string name);

            void loadSFX(std::string location, std::string name);
            sf::Sound* getSound(std::string name);

            void specifyMusicLocation(std::string location, std::string name);
            std::string getMusicLocation(std::string name);

        private:
            std::unordered_map<std::string, sge::TextureSheet*> m_textures;
            std::unordered_map<std::string, sf::Font*> m_fonts;
            std::unordered_map<std::string, std::pair<sf::SoundBuffer*, sf::Sound*>> m_sfx;
            std::unordered_map<std::string, std::string> m_musicLocations;
    };
}


#endif