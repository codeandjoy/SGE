#include <SFML/Graphics.hpp>
using namespace sf;

class Universe{
    public:
        Universe(RenderWindow &window);

        void loop();

    private:
        RenderWindow *windowPtr;
};