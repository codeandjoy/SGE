#ifndef PLAIN_ENTITY_H
#define PLAIN_ENTITY_H

#include <SFML/Graphics.hpp>

#include "../Entity.h"
#include "../../Sprite/Sprite.h"


namespace sge{
    class PlainEntity : public sge::Entity{
        public:
            PlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
                sprite = new sge::Sprite(*texture, textureRect);
                sprite->setPosition(position);
            }
    };
}


#endif