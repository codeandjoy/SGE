#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include <SFML/Graphics.hpp>
#include "CollisionShapePositionData.h"
#include "../Physics/PhysicalObject.h"


class CollisionShape : public sf::RectangleShape{
    public:
        CollisionShape(PhysicalObject *_owner);

        PhysicalObject* getOwner();

        CollisionShapePositionData getPositionData();

        sf::Vector2f getOffset();
        void setOffset(sf::Vector2f _offset);

        void setSize(const sf::Vector2f& size);

        // Border
        bool getIsVisible();
        void setIsVisible(bool is);

        sf::RectangleShape* getBorder();
        void setBorderThickness(float thickness);
        void setBorderColor(const sf::Color& color);
        //

        void align();

    private:
        PhysicalObject *owner;

        sf::Vector2f offset = sf::Vector2f(0, 0);

        bool isVisible = true;
        sf::RectangleShape border;
};


#endif