#include <SFML/Graphics.hpp>
using namespace sf;

class Entity: public RectangleShape{
    public:
        Entity();

        void move(Vector2f movement);
};