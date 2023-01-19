#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "Animation.h"


class Universe{
    public:
        void setupWindow(sf::RenderWindow *window);
        void createPlayer(sf::Sprite *player);
        void addMap(std::vector<sf::Sprite*> *map); // TODO managed in Scene in the future(?)
        void addController(const std::function<void (sf::Event event)> &lambdaController);
        void addAnimation(Animation *animation);

        void loop();

        PhysicsManager physicsManager;
        CollisionManager collisionManager;

    private:
        sf::RenderWindow *windowPtr;
        sf::Sprite *playerPtr;
        std::vector<sf::Sprite*> *mapPtr;
        std::vector<std::function<void (sf::Event event)>> controllers;
        std::vector<Animation*> animations;
};


#endif