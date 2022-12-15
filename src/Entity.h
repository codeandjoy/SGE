#include <SFML/Graphics.hpp>
using namespace sf;

class Entity: public RectangleShape{
    public:
        Entity();

        void setIsMovingTop(bool is);
        void setIsMovingBottom(bool is);
        void setIsMovingRight(bool is);
        void setIsMovingLeft(bool is);
        
        void update();
        void move(Vector2f movement);

    private:
        bool isMovingTop;
        bool isMovingBottom;
        bool isMovingRight;
        bool isMovingLeft;
};