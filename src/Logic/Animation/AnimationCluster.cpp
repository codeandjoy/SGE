#include "AnimationCluster.h"
#include "../../Assets/Texture/TextureSheet.h"
#include "TextureSequence.h"


void sge::AnimationCluster::addTextureSequence(std::string name, TextureSequence* textureSequence){ m_textureSequences[name] = textureSequence; }
void sge::AnimationCluster::setCurrentTextureSequence(std::string name){
    m_clock.restart();
    m_currentTextureSequence = name;
    m_currentTextureN = 0;

    m_updateTexture();
}
std::string sge::AnimationCluster::getCurrentTextureSequence(){ return m_currentTextureSequence; }


void sge::AnimationCluster::run(){
    if(!m_textureSequences.size()){
        printf("No texture sequences initialized.\n");
        exit(1);
    }
    if(!m_currentTextureSequence.length()){
        printf("Can not run AnimationCluster if no current texture sequence is set.\n"); // ? Default to first added ?
        exit(1);
    }

    if(m_clock.getElapsedTime().asMilliseconds() > animationDelayMilliseconds){
        m_updateTexture();

        if(m_currentTextureN+1 == m_textureSequences[m_currentTextureSequence]->sequenceRects.size()){
            m_currentTextureN = 0;
        }
        else m_currentTextureN++;

        m_clock.restart();
    }
}


void sge::AnimationCluster::m_updateTexture(){
    m_ownerSpritePtr->setTexture(*m_textureSequences[m_currentTextureSequence]->textureSheet->getTexture());
    m_ownerSpritePtr->setTextureRect(m_textureSequences[m_currentTextureSequence]->sequenceRects[m_currentTextureN]);
}