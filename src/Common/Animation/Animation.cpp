#include "Animation.h"
#include "../../Assets/Texture/TextureSheet.h"


sge::Animation::Animation(sge::TextureSheet* textureSheet, sf::Sprite* ownerSprite, int initialTextureN){
    m_textureSheet = textureSheet;
    m_ownerSpritePtr = ownerSprite;
    
    m_ownerSpritePtr->setTexture(*textureSheet->getTexture());
    m_ownerSpritePtr->setTextureRect(textureSheet->getTextureRect(initialTextureN));
}



void sge::Animation::addTextureSequence(std::string name, std::vector<int> textureSequence){ m_textureSequences[name] = textureSequence; }
void sge::Animation::setCurrentTextureSequence(std::string name){
    m_clock.restart();
    m_currentTextureSequence = name;
    m_currentTextureN = 0;

    m_ownerSpritePtr->setTextureRect(m_textureSheet->getTextureRect(m_textureSequences[m_currentTextureSequence].at(m_currentTextureN)));
}



void sge::Animation::runForward(){
    if(!m_textureSequences.size()){
        printf("No texture sequences initialized.\n");
        exit(1);
    }
    if(!m_currentTextureSequence.length()){
        printf("Can not run animation if no current texture sequence is set.\n"); // ? Default to first added ?
        exit(1);
    }

    if(m_clock.getElapsedTime().asMilliseconds() > animationDelayMilliseconds){
        m_ownerSpritePtr->setTextureRect(m_textureSheet->getTextureRect(m_textureSequences[m_currentTextureSequence].at(m_currentTextureN)));
        
        if(m_currentTextureN+1 == m_textureSequences[m_currentTextureSequence].size()){
            m_currentTextureN = 0;
        }
        else m_currentTextureN++;

        m_clock.restart();
    }
}