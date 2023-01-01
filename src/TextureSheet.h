#ifndef TEXTURESHEET_H
#define TEXTURESHEET_H


#include <SFML/Graphics.hpp>
#include "TextureSheetSizes.h"

// TODO textureset with gaps
class TextureSheet{
    public:
        TextureSheet(TextureSheetSizes tss, std::string location);

        std::string getLocation();
        sf::Texture* getTextureSheet();
        sf::IntRect getTextureRect(int textureN);

    private:
        std::string location; // texture sheet image location
        sf::Texture textureSheet;
        std::vector<sf::IntRect> textureRects;
};


#endif