#ifndef COLLISION_SHAPE_BORDER_H
#define COLLISION_SHAPE_BORDER_H

#include <SFML/Graphics.hpp>


namespace sge{
    class CollisionShape;
    struct CollisionShapeBorderSettings;

    class CollisionShapeBorder : public sf::RectangleShape{
        public:
            CollisionShapeBorder(sge::CollisionShape* owner, sge::CollisionShapeBorderSettings settings);
    };
}


#endif