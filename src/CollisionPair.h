#ifndef COLLISION_PAIR_H
#define COLLISION_PAIR_H

#include <SFML/Graphics.hpp> 


// ? add collision type specifier (rectangle, circle etc.)
struct CollisionPair{
    std::tuple<std::string, std::string> collisionGroups;
    std::vector<std::function<void(sf::Sprite *sprite1, sf::Sprite *sprite2)>> collisionResponses; // TODO allow function with and without parameters (struct || simply register different types of functions and use the one that exists (or all of them))
};


#endif