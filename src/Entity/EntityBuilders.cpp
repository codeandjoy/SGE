#include "EntityBuilders.h"

#include "./Entity.h"
#include "../Physics/Computations.h"
#include "../Physics/PhysicalObject.h"
#include "../Collision/CollisionShape.h"


Entity* buildPlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    Entity* e = new Entity{ new PhysicalObject() };
    e->physicalObject->setTexture(*texture);
    e->physicalObject->setTextureRect(textureRect);
    e->physicalObject->setPosition(position);

    return e;
}

Entity* buildStaticEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    Entity* e = buildPlainEntity(texture, textureRect, position);

    e->collisionShapes["globalBounds"] = new CollisionShape(e);

    return e;
}

Entity* buildMobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    Entity* e = buildStaticEntity(texture, textureRect, position);

    e->physicalObject->createContinuousComputation("updateVelocity", updateVelocityBasedOnAcceleration(e->physicalObject));
    e->physicalObject->createContinuousComputation("updatePosition", updatePositionBasedOnVelocity(e->physicalObject));

    return e;
}