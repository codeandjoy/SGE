#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "../Texture/TextureSheet.h"


// TODO Animations should switch immediately
class Animation{
    public:
        Animation(TextureSheet *spritesheet, sf::Sprite *owner, int initialTextureN);
    
        // ?
        // runForward -> 1,2,3,1,2,3
        // runCycle -> 1,2,3,2,1,2
        // ?
        void run();
        void restartClock();
        void setCurrentAnimationSequence(std::string sequenceName);
        void addAnimationSequence(std::string sequenceName, std::vector<int> textureSequence);

    private:
        sf::Sprite *owner;
        TextureSheet *textureSheet;
        
        sf::Clock clock;
        std::map<std::string, std::vector<int>> animationSequences; // e.g. "idle": [5, 6, 7, 8]
        std::string currentAnimationSequence;
        int currentTextureN = 0;

};


#endif