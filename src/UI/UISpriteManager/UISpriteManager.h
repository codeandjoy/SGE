#ifndef UI_SPRITE_MANAGER_H
#define UI_SPRITE_MANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>


namespace sge{
    class UISpriteManager{
        public:
            void registerSprite(sf::Sprite* sprite);
            void deregisterSprite(sf::Sprite* sprite);
            std::vector<sf::Sprite*> getAllVisibleSprites();

            void showSprite(sf::Sprite* sprite);
            void hideSprite(sf::Sprite* sprite);

            void drawUISprites(sf::RenderWindow* windowPtr);

        private:
            std::vector<sf::Sprite*> m_visibleSprites;
            std::vector<sf::Sprite*> m_hiddenSprites;
    };
}


#endif