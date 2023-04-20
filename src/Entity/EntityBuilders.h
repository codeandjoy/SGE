#ifndef ENTITY_BUILDERS_H
#define ENTITY_BUILDERS_H

#include "./Entity.h"
#include "../Physics/computations.h"
#include "../Physics/PhysicalObject.h"
#include "../Collision/CollisionShape.h"


// Plain entity - Entity that consists only of PhysicalObject
Entity* buildPlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    Entity* e = new Entity{ new PhysicalObject() };
    e->physicalObject->setTexture(*texture);
    e->physicalObject->setTextureRect(textureRect);
    e->physicalObject->setPosition(position);

    return e;
}

// Static entity - Plain entity that has >= 1 CollisionShape(s)
Entity* buildStaticEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    Entity* e = buildPlainEntity(texture, textureRect, position);

    e->collisionShapes["globalBounds"] = new CollisionShape(e->physicalObject);

    return e;
}

// Mobile entity - Static entity that has calculations that allow mobility
Entity* buildMobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    Entity* e = buildStaticEntity(texture, textureRect, position);

    e->physicalObject->createContinuousComputation("updateVelocity", updateVelocityBasedOnAcceleration(e->physicalObject));
    e->physicalObject->createContinuousComputation("updatePosition", updatePositionBasedOnVelocity(e->physicalObject));

    return e;
}


#endif