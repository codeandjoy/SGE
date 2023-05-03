#ifndef CLICKABLE_SHAPE_H
#define CLICKABLE_SHAPE_H

#include <functional>
#include <SFML/Graphics.hpp>
#include "../../Collision/CollisionShape.h"


namespace sge{
    struct ClickableShape : public CollisionShape{
        std::function<void(sf::Event event)> clickHandler;
    };
}


#endif