#ifndef ENTITY_BUILDERS_H
#define ENTITY_BUILDERS_H

#include <SFML/Graphics.hpp>


namespace sge{
    class Entity;
    
    // Builds sge::Entity that consists only of sf::Sprite*
    Entity* buildPlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);

    // Builds sge::Entity that consists of sf::Sprite* and "globalBounds" -> sge::CollisionShape*
    Entity* buildStaticEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);

    // Builds sge::Entity that consists of sf::Sprite*, sge::PhysicalObject* and "globalBounds" -> sge::CollisionShape*
    //
    // PhysicalObject added continuous computations:
    // "updateVelocity" -> updateVelocityBasedOnAcceleration()
    // "updatePosition" -> updatePositionBasedOnVelocity()
    Entity* buildMobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);
}


#endif