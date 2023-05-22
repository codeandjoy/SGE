#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>


namespace sge{
    class SpriteManager{
        public:
            void registerSprite(sf::View*, sf::Sprite* sprite);
            void deregisterSprite(sf::View*, sf::Sprite* sprite);
            void deregisterAllSprites();
            std::vector<sf::Sprite*> getViewSprites(sf::View* view);

            void drawSprites(sf::RenderWindow* windowPtr);

        private:
            std::unordered_map<sf::View*, std::vector<sf::Sprite*>> m_sprites;
    };
}


#endif