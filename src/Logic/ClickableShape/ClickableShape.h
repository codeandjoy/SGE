#ifndef CLICKABLE_SHAPE_H
#define CLICKABLE_SHAPE_H

#include <functional>
#include <SFML/Graphics.hpp>
#include "../../Logic/CollisionShape/CollisionShape.h"


namespace sge{
    class Entity;

    class ClickableShape : public sf::RectangleShape{
        public:
            ClickableShape(sge::Entity* ownerEntity);

            std::function<void(sge::ClickableShape* thisClickableShape, sf::Event event)> action;
            
            sf::Vector2f offset = sf::Vector2f(0, 0);

            
            sge::Entity* getOwnerEntity();
            void align();

        private:
            sge::Entity* m_ownerEntityPtr;
    };
}


#endif