#include "SpriteManager.h"
#include "Sprite.h"


void sge::SpriteManager::draw(sf::RenderWindow* window){
    for(auto [view, sprites] : m_components){
        window->setView(*view);

        for(sge::Sprite* sprite : sprites){
            window->draw(*sprite);
        }
    }
}