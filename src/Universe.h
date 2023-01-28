#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "PhysicalObject.h"
#include "Animation.h"


class Universe{
    public:
        void setupWindow(sf::RenderWindow *window);
        void createPlayer(sf::Sprite *player);
        void addMap(std::vector<PhysicalObject*> *map); // TODO managed in Scene in the future(?)
        void addController(const std::function<void()> &lambdaController);
        void addAnimation(Animation *animation);

        void loop();

        PhysicsManager physicsManager;
        CollisionManager collisionManager;

    private:
        sf::Clock deltaClock;
        sf::RenderWindow *windowPtr;
        sf::Sprite *playerPtr; // ! for drawing
        std::vector<PhysicalObject*> *mapPtr; // ! for drawing
        std::vector<std::function<void()>> controllers;
        std::vector<Animation*> animations;
};


#endif