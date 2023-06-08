#include "DebugScreenManager.h"
#include "DebugVariable.h"
#include "../../Logic/Entity/Entity.h"
#include "../../Logic/Entity/EntityManager.h"
#include "../../Logic/Sprite/Sprite.h"
#include "../../Logic/SpriteText/SpriteText.h"


void sge::DebugScreenManager::addDebugVariable(sf::Vector2f position, sge::DebugVariable* debugVariable){
    sge::Entity* textEntity = new sge::Entity();
    textEntity->sprite = new sge::Sprite();
    textEntity->sprite->setPosition(position);

    textEntity->spriteText = new sge::SpriteText(textEntity->sprite);
    textEntity->spriteText->setCharacterSize(m_fontSize);
    textEntity->spriteText->setFont(*m_font);
    textEntity->spriteText->setString(debugVariable->value);

    m_entityManagerPtr->registerComponent(m_view, textEntity);
    m_debugVariables[debugVariable] = textEntity;
}

std::unordered_map<sge::DebugVariable*, sge::Entity*> sge::DebugScreenManager::getDebugVariables(){ return m_debugVariables; }


void sge::DebugScreenManager::updateDebugVariables(){
    for(auto& [debugVariable, textEntity] : m_debugVariables){
        debugVariable->update();
        textEntity->spriteText->setString(debugVariable->value);
    }
}