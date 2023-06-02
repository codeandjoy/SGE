#include "SpriteManager.h"


void sge::SpriteManager::draw(sf::RenderWindow* window){
    for(auto [view, sprites] : m_components){
        window->setView(*view);

        for(sf::Sprite* sprite : sprites){
            window->draw(*sprite);
        }
    }
}