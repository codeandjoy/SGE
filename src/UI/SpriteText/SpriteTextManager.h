#ifndef SPRITE_TEXT_MANAGER_H
#define SPRITE_TEXT_MANAGER_H

#include <vector>


namespace sge{
    class SpriteText;

    class SpriteTextManager{
        public:
            void registerSpriteText(sge::SpriteText* spriteText);
            void deregisterSpriteText(sge::SpriteText* spriteText);
            std::vector<sge::SpriteText*> getAllVisibleSpriteTextObjects();


            void showSpriteText(sge::SpriteText* spriteText);
            void hideSpriteText(sge::SpriteText* spriteText);


            void alignSpriteTextObjects();

        private:
            std::vector<sge::SpriteText*> m_visibleSpriteTextObjects;
            std::vector<sge::SpriteText*> m_hiddenSpriteTextObjects;
    };  
}


#endif