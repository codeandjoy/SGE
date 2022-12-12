#include <SFML/Graphics.hpp>
#include "Entity.h"
using namespace sf;
using namespace std;



class Universe{
    public:
        void createMap(const string mapDataFileLocation);
        void createPlayer(Entity &player);
        void setupWindow(RenderWindow &window);
        void addController(const function<void (Event event)> &lambdaController);
        void loop();

    private:
        RenderWindow *windowPtr;
        vector<RectangleShape> map;
        vector<function<void (Event event)>> controllers;
        Entity *playerPtr;
};