#ifndef CLICKABLE_SHAPE_HELPERS_H
#define CLICKABLE_SHAPE_HELPERS_H

#include <SFML/Graphics.hpp>


namespace sge{
    class ClickableShape;

    bool isMouseOverClickableShape(ClickableShape* clickableShape, sf::RenderWindow* window);
}


#endif