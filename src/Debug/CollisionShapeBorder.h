#ifndef COLLISION_SHAPE_BORDER_H
#define COLLISION_SHAPE_BORDER_H

#include <SFML/Graphics.hpp>
class CollisionShape;
struct CollisionShapeBorderSettings;


class CollisionShapeBorder : public sf::RectangleShape{
    public:
        CollisionShapeBorder(CollisionShape* owner, CollisionShapeBorderSettings settings);
};


#endif