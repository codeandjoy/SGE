#include <algorithm>

#include "SpriteTextManager.h"
#include "SpriteText.h"


void sge::SpriteTextManager::update(float dt){
    for(auto& [_, spriteTextObjects] : m_components){
        for(sge::SpriteText* spriteText : spriteTextObjects){
            spriteText->align();
        }
    }
}
void sge::SpriteTextManager::draw(sf::RenderWindow* window){
    for(auto& [view, spriteTextObjects] : m_components){
        window->setView(*view);

        for(SpriteText* spriteText : spriteTextObjects){
            window->draw(*spriteText);
        }
    }
}