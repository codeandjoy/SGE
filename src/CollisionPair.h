#ifndef COLLISION_PAIR_H
#define COLLISION_PAIR_H

#include <SFML/Graphics.hpp> 


// ? add collision type specifier (rectangle, circle etc.)
struct CollisionPair{
    std::tuple<std::string, std::string> collisionGroups;
    std::vector<std::function<void()>> collisionResponses;

    CollisionPair(std::tuple<std::string, std::string> collisionGroups_){
        collisionGroups = collisionGroups_;
    }
};


#endif