#ifndef TEXTURESHEET_H
#define TEXTURESHEET_H

#include <SFML/Graphics.hpp>
#include "TextureSheetSizes.h"


// TODO texturesheet with gaps between textures
class TextureSheet{
    public:
        TextureSheet(TextureSheetSizes tss, std::string location);

        // TODO make names shorter
        std::string getLocation();
        sf::Texture* getTextureSheet();
        sf::IntRect getTextureRect(int textureN);

    private:
        std::string location;
        sf::Texture textureSheet;
        std::vector<sf::IntRect> textureRects;
};


#endif