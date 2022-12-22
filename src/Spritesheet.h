#ifndef SPRITESHEET_H
#define SPRITESHEET_H


#include <SFML/Graphics.hpp>

class Spritesheet{
    public:
        Spritesheet(int textureSizeX, int textureSizeY, int numTexturesX, int numTexturesY, std::string spritesheetLocation);

        sf::Texture* getSpritesheet();
        sf::IntRect getCoordinates(int n);

    private:
        sf::Texture spritesheet;
        std::vector<sf::IntRect> coordinates;
};


#endif