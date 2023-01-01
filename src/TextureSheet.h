#ifndef TEXTURESHEET_H
#define TEXTURESHEET_H


#include <SFML/Graphics.hpp>

// TODO textureset with gaps
class TextureSheet{
    public:
        TextureSheet(int textureSizeX, int textureSizeY, int numTexturesX, int numTexturesY, std::string textureSheetLocation);

        sf::Texture* getTextureSheet();
        sf::IntRect getTextureRect(int textureN);

    private:
        std::string textureSheetLocation; // texture sheet image location
        sf::Texture textureSheet;
        std::vector<sf::IntRect> textureRects;
};


#endif