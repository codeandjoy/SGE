#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>


namespace sge{
    class SpriteManager{
        public:
            void registerSprite(sf::Sprite* sprite);
            void deregisterSprite(sf::Sprite* sprite);
            void deregisterAllSprites();
            std::vector<sf::Sprite*> getSprites();            

            void drawSprites(sf::RenderWindow* windowPtr);

        private:
            std::vector<sf::Sprite*> m_sprites;
    };
}


#endif