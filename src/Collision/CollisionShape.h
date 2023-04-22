#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

class Entity;
struct Measurements;


class CollisionShape : public sf::RectangleShape{
    public:
        CollisionShape(Entity* ownerEntityPtr);

        sf::Vector2f offset = sf::Vector2f(0, 0);

        Entity* getOwnerEntity();
        Measurements getMeasurements();
        void align();

    private:
        Entity* m_ownerEntityPtr;
};


#endif