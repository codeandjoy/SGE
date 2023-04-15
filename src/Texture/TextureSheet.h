#ifndef TEXTURESHEET_H
#define TEXTURESHEET_H

#include <SFML/Graphics.hpp>
#include "TextureSheetSizes.h"


// TODO texturesheet with gaps between textures
// ? parse from .tsx ?
class TextureSheet{
    public:
        TextureSheet(TextureSheetSizes textureSheetSizes, std::string location);

        std::string getLocation();
        sf::Texture* getTextureSheet();
        sf::IntRect getTextureRect(int textureN);

    private:
        std::string m_location;
        sf::Texture m_textureSheet;
        std::vector<sf::IntRect> m_textureRects;
};


#endif