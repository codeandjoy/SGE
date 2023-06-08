#ifndef ANIMATION_CLUSTER_H
#define ANIMATION_CLUSTER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../Component/StatefulComponent.h"


namespace sge{
    class TextureSequence;

    class AnimationCluster : public sge::StatefulComponent{
        public:
            AnimationCluster(sf::Sprite* ownerSprite) : m_ownerSpritePtr(ownerSprite){};
        
            int animationDelayMilliseconds = 100;
            
            void addTextureSequence(std::string name, TextureSequence* animationSequence);
            void setCurrentTextureSequence(std::string name);
            std::string getCurrentTextureSequence();
                    
            void run();

        private:
            sf::Sprite* m_ownerSpritePtr;
            
            std::unordered_map<std::string, TextureSequence*> m_textureSequences;
            void m_updateTexture();

            sf::Clock m_clock;
            std::string m_currentTextureSequence;
            int m_currentTextureN = 0;
    };
}


#endif