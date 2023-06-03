#include "EntityBuilders.h"

#include "./Entity.h"
#include "../Sprite/Sprite.h"
#include "../Physics/Computations.h"
#include "../Physics/PhysicalObject.h"
#include "../CollisionShape/CollisionShape.h"


sge::Entity* sge::buildPlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    sge::Entity* e = new sge::Entity{ new sge::Sprite() };
    e->sprite->setTexture(*texture);
    e->sprite->setTextureRect(textureRect);
    e->sprite->setPosition(position);

    return e;
}

sge::Entity* sge::buildVoidEntity(sf::Vector2f size, sf::Vector2f position){
    sge::Entity* e = new sge::Entity{ new sge::Sprite() };
    e->sprite->setPosition(position);

    e->collisionShapes["globalBounds"] = new sge::CollisionShape(e);
    e->collisionShapes["globalBounds"]->setSize(size);

    return e;
}

sge::Entity* sge::buildStaticEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    sge::Entity* e = sge::buildPlainEntity(texture, textureRect, position);

    e->collisionShapes["globalBounds"] = new sge::CollisionShape(e);

    return e;
}

sge::Entity* sge::buildMobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    sge::Entity* e = sge::buildStaticEntity(texture, textureRect, position);

    e->physicalObject = new PhysicalObject(e->sprite);

    e->physicalObject->createContinuousComputation("updateVelocity", sge::updateVelocityBasedOnAcceleration());
    e->physicalObject->createContinuousComputation("updatePosition", sge::updatePositionBasedOnVelocity());

    return e;
}