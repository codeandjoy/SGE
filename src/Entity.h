#ifndef ENTITY_H
#define ENTITY_H


#include <SFML/Graphics.hpp>

class Entity: public sf::Sprite{
    public:
        Entity();

        // Todo setDirection(direction) ?
        void setIsMovingTop(bool is);
        void setIsMovingBottom(bool is);
        void setIsMovingRight(bool is);
        void setIsMovingLeft(bool is);
        
        void update();
        void move(sf::Vector2f movement);

    private:
        bool isMovingTop = false;
        bool isMovingBottom = false;
        bool isMovingRight = false;
        bool isMovingLeft = false;
};


#endif