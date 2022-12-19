#ifndef ENTITY_H
#define ENTITY_H


#include <SFML/Graphics.hpp>

class Entity: public sf::RectangleShape{
    public:
        Entity();

        void setIsMovingTop(bool is);
        void setIsMovingBottom(bool is);
        void setIsMovingRight(bool is);
        void setIsMovingLeft(bool is);
        
        void update();
        void move(sf::Vector2f movement);

    private:
        bool isMovingTop;
        bool isMovingBottom;
        bool isMovingRight;
        bool isMovingLeft;
};


#endif