#ifndef SPRITE_TEXT_MANAGER_H
#define SPRITE_TEXT_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

namespace sge{
    class SpriteText;

    class SpriteTextManager{
        public:
            void registerSpriteText(sf::View* view, sge::SpriteText* spriteText);
            void deregisterSpriteText(sf::View* view, sge::SpriteText* spriteText);
            std::vector<sge::SpriteText*> getSpriteTextObjectsByView(sf::View* view);
            std::unordered_map<sf::View*, std::vector<sge::SpriteText*>> getSpriteTextObjectsMap();


            void alignSpriteTextObjects();
            void drawSpriteTextObjects(sf::RenderWindow* windowPtr);

        private:
            std::unordered_map<sf::View*, std::vector<sge::SpriteText*>> m_spriteTextObjects;
    };  
}


#endif