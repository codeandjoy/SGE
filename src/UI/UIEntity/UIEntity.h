#ifndef UI_ENTITY_H
#define UI_ENTITY_H

#include <SFML/Graphics.hpp>


namespace sge{
    struct ClickableShape;
    class SpriteText;
    class Animation;

    struct UIEntity{
        sf::Sprite* sprite;
        sge::ClickableShape* clickableShape = nullptr;
        sge::SpriteText* spriteText = nullptr;
        sge::Animation* animation = nullptr;
    };
}


#endif