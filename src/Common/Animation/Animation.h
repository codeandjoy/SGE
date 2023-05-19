#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <vector>


namespace sge{
    class TextureSheet;

    // TODO Animations should switch immediately
    class Animation{
        public:
            Animation(sge::TextureSheet* textureSheet, sf::Sprite* ownerSprite, int initialTextureN);
        
            int animationDelayMilliseconds = 100;
            
            void addTextureSequence(std::string name, std::vector<int> textureSequence);
            void setCurrentTextureSequence(std::string name);
        
            void runForward();
            // TODO
            // animationType : forward or cycle, run function in manager based on animation type
            // runCycle()  1 2 3 2 1

        private:
            sf::Sprite* m_ownerSpritePtr;
            sge::TextureSheet* m_textureSheet;
            
            sf::Clock m_clock;
            std::unordered_map<std::string, std::vector<int>> m_textureSequences; // e.g. "idle": [5, 6, 7, 8]
            std::string m_currentTextureSequence;
            int m_currentTextureN = 0;

    };
}


#endif