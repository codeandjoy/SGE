#ifndef ENTITY_BUILDERS_H
#define ENTITY_BUILDERS_H

#include <SFML/Graphics.hpp>
class Entity;


// Plain entity - Entity that consists only of PhysicalObject
Entity* buildPlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);

// Static entity - Plain entity that has >= 1 CollisionShape(s)
Entity* buildStaticEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);

// Mobile entity - Static entity that has calculations that allow mobility
Entity* buildMobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);


#endif