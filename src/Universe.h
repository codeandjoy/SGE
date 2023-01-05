#ifndef UNIVERSE_H
#define UNIVERSE_H


#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "PhysicalObject.h"
#include "Animation.h"


class Universe{
    public:
        void addMap(std::vector<sf::Sprite> *map); // TODO managed in Scene in the future(?)
        void createPlayer(Entity *player);
        void setupWindow(sf::RenderWindow *window);
        void addController(const std::function<void (sf::Event event)> &lambdaController);
        void addPhysicalObject(PhysicalObject *physicalObject);
        void addAnimation(Animation *animation);
        void loop();

    private:
        sf::RenderWindow *windowPtr;
        std::vector<sf::Sprite> *mapPtr;
        std::vector<std::function<void (sf::Event event)>> controllers;
        Entity *playerPtr;
        std::vector<PhysicalObject*> physicalObjects;
        std::vector<Animation*> animations;
};


#endif