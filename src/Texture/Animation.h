#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "../Texture/TextureSheet.h"


// TODO Animations should switch immediately
class Animation{
    public:
        Animation(TextureSheet* textureSheet, sf::Sprite* owner, int initialTextureN);
    
        
        void addTextureSequence(std::string name, std::vector<int> textureSequence);
        void setCurrentTextureSequence(std::string name);
    

        // ?
        // runForward -> 1,2,3,1,2,3
        // runCycle -> 1,2,3,2,1,2
        // ?
        void run();
        void restartClock();

    private:
        sf::Sprite* m_owner;
        TextureSheet* m_textureSheet;
        
        sf::Clock m_clock;
        std::map<std::string, std::vector<int>> m_textureSequences; // e.g. "idle": [5, 6, 7, 8]
        std::string m_currentTextureSequence;
        int m_currentTextureN = 0;

};


#endif