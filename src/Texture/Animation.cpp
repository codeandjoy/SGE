#include "Animation.h"

Animation::Animation(TextureSheet* textureSheet, sf::Sprite* owner, int initialTextureN){
    m_textureSheet = textureSheet;
    m_owner = owner;
    
    m_owner->setTexture(*textureSheet->getTextureSheet());
    m_owner->setTextureRect(textureSheet->getTextureRect(initialTextureN));
}



void Animation::addTextureSequence(std::string name, std::vector<int> textureSequence){ m_textureSequences[name] = textureSequence; }
void Animation::setCurrentTextureSequence(std::string name){
    if(m_currentTextureSequence != name){
        m_currentTextureSequence = name;
        m_currentTextureN = 0;
        m_clock.restart();
    }
}



void Animation::run(){
    if(!m_textureSequences.size()){
        printf("No texture sequences initialized.\n");
        exit(1);
    }
    if(!m_currentTextureSequence.length()){
        printf("Can not run animation if no current texture sequence is set.\n"); // ? Default to first added ?
        exit(1);
    }

    // TODO dynamic animation delay (for each animation ?)
    if(m_clock.getElapsedTime().asMilliseconds() > 100){
        m_owner->setTextureRect(m_textureSheet->getTextureRect(m_textureSequences[m_currentTextureSequence].at(m_currentTextureN)));
        
        if(m_currentTextureN+1 == m_textureSequences[m_currentTextureSequence].size()){
            m_currentTextureN = 0;
        }
        else m_currentTextureN++;

        
        m_clock.restart();
    }
}
void Animation::restartClock(){ m_clock.restart(); }
