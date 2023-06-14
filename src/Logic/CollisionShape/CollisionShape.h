#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "../../Structure/Component/StatefulComponent.h"


namespace sge{
    class Entity;
    struct Measurements;

    class CollisionShape : public sge::StatefulComponent, public sf::RectangleShape{
        public:
            CollisionShape(sge::Entity* ownerEntity);

            sf::Vector2f offset = sf::Vector2f(0, 0);
            std::vector<std::string> collisionGroups;

            sge::Entity* getOwnerEntity();
            sge::Measurements getMeasurements();
            void align();

        private:
            sge::Entity* m_ownerEntityPtr;
    };
}


#endif