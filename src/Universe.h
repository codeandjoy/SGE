#ifndef UNIVERSE_H
#define UNIVERSE_H


#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "PhysicalObject.h"
#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "Animation.h"


class Universe{
    public:
        void addMap(std::vector<sf::Sprite*> *map); // TODO managed in Scene in the future(?)
        void createPlayer(sf::Sprite *player);
        void setupWindow(sf::RenderWindow *window);
        void addController(const std::function<void (sf::Event event)> &lambdaController);
        void addAnimation(Animation *animation);
        void loop();

        PhysicsManager physicsManager;
        CollisionManager collisionManager;

    private:
        sf::RenderWindow *windowPtr;
        std::vector<sf::Sprite*> *mapPtr;
        std::vector<std::function<void (sf::Event event)>> controllers;
        sf::Sprite *playerPtr;
        std::vector<Animation*> animations;
};


#endif