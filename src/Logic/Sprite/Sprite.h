#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>
#include "../../Component/StatefulComponent.h"


namespace sge{
    class Sprite : public sge::StatefulComponent, public sf::Sprite{
        public:
            Sprite() : sf::Sprite(){};
            Sprite(const sf::Texture& texture) : sf::Sprite(texture){};
            Sprite(const sf::Texture& texture, const sf::IntRect& rectangle) : sf::Sprite(texture, rectangle){};
    };
}



#endif