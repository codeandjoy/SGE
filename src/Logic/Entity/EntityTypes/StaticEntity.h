#ifndef STATIC_ENTITY_H
#define STATIC_ENTITY_H

#include "PlainEntity.h"
#include "../../CollisionShape/CollisionShape.h"


namespace sge{
    class StaticEntity : public sge::PlainEntity{
        public:
            StaticEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups)
                : sge::PlainEntity(texture, textureRect, position){
                    collisionShapes["global_bounds"] = new sge::CollisionShape(this);
                    collisionShapes["global_bounds"]->collisionGroups = collisionGroups;
                }
    };
}



#endif