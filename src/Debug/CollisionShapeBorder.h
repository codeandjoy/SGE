#ifndef COLLISION_SHAPE_BORDER_H
#define COLLISION_SHAPE_BORDER_H

#include "../Collision/CollisionShape.h"
#include "./CollisionShapeBorderSettings.h"


class CollisionShapeBorder : public sf::RectangleShape{
    public:
        CollisionShapeBorder(CollisionShape* owner, CollisionShapeBorderSettings settings);
};


#endif