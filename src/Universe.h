#ifndef UNIVERSE_H
#define UNIVERSE_H


#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "PhysicalObject.h"


class Universe{
    public:
        void createMap(const std::string mapDataFileLocation);
        void createPlayer(Entity &player);
        void setupWindow(sf::RenderWindow &window);
        void addController(const std::function<void (sf::Event event)> &lambdaController);
        void addPhysicalObject(PhysicalObject *physicalObject);
        void loop();

    private:
        sf::RenderWindow *windowPtr;
        std::vector<sf::RectangleShape> map;
        std::vector<std::function<void (sf::Event event)>> controllers;
        Entity *playerPtr;
        std::vector<PhysicalObject*> physicalObjects;
};


#endif