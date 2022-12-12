#include <SFML/Graphics.hpp>
#include "Entity.h"
using namespace sf;
using namespace std;



class Universe{
    public:
        void createMap(const string mapDataFileLocation);
        void createPlayer(Entity &player);
        void setupWindow(RenderWindow &window);
        void loop();

    private:
        RenderWindow *windowPtr;
        vector<RectangleShape> map;
        Entity *playerPtr;
};