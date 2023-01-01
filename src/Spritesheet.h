#ifndef SPRITESHEET_H
#define SPRITESHEET_H


#include <SFML/Graphics.hpp>

// TODO spritesheet with gaps
class Spritesheet{
    public:
        Spritesheet(int textureSizeX, int textureSizeY, int numTexturesX, int numTexturesY, std::string spritesheetLocation);

        sf::Texture* getSpritesheet();
        sf::IntRect getTextureRect(int textureN);

    private:
        sf::Texture spritesheet;
        std::vector<sf::IntRect> textureRects;
};


#endif