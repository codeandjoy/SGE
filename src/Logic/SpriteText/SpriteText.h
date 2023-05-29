#ifndef SPRITE_TEXT_H
#define SPRITE_TEXT_H

#include <SFML/Graphics.hpp>


namespace sge{
    class SpriteText : public sf::Text{
        public:
            SpriteText(sf::Sprite* ownerSprite);

            sf::Vector2f offset = sf::Vector2f(0, 0);

            void align();
        
        private:
            sf::Sprite* m_ownerSpritePtr;
    };
}


#endif