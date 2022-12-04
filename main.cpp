#include <SFML/Graphics.hpp>
using namespace sf;

int main(){
    RenderWindow window(VideoMode(1200, 800), "Test", Style::Fullscreen);
    
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(
                event.type == Event::Closed ||
                event.type == Event::KeyPressed && event.key.code == Keyboard::Q
                ) window.close();
        }
    }

    return 0;
}