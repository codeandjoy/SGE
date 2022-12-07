#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;



class Universe{
    public:
        void createMap(const string mapDataFileLocation);
        void setupWindow(RenderWindow &window);
        void loop();

    private:
        RenderWindow *windowPtr;
        vector<RectangleShape> map;
};