#ifndef VOID_ENTITY_H
#define VOID_ENTITY_H

#include <SFML/Graphics.hpp>

#include "../Entity.h"
#include "../../Sprite/Sprite.h"
#include "../../CollisionShape/CollisionShape.h"


namespace sge{
    class VoidEntity : public sge::Entity{
        public:
            VoidEntity(sf::Vector2f size, sf::Vector2f position, std::vector<std::string> collisionGroups){
                sprite = new sge::Sprite();
                sprite->setPosition(position);
                
                collisionShapes["global_bounds"] = new sge::CollisionShape(this);
                collisionShapes["global_bounds"]->setSize(size);
                collisionShapes["global_bounds"]->collisionGroups = collisionGroups;
            }
    };
}



#endif