#include <filesystem>
#include "../../SGE.hpp"


int main(){
    sge::Universe* universe = new sge::Universe();

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    sf::View *view = new sf::View(sf::Vector2f(125, 75), sf::Vector2f(250, 150));
    window->setView(*view);
    window->setKeyRepeatEnabled(false); // For proper keyboard events handling (e.g. jumping)
    
    universe->setupWindow(window);



    universe->assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/ui/assets/ButtonSpritesheet.png", "button", sge::TextureSheetSizes{32, 32, 1, 2});
    universe->assetsManager->loadFont(std::filesystem::current_path().string() + "/examples/ui/assets/m5x7.ttf", "m5x7");
    


    int clickCount = 0;



    sge::UIEntity* uiTextEntity = new sge::UIEntity{ new sf::Sprite() };
    uiTextEntity->sprite->setPosition(125, 40);

    sge::SpriteText* spriteText = new sge::SpriteText(uiTextEntity->sprite);
    spriteText->setFont(*universe->assetsManager->getFont("m5x7"));
    spriteText->setString(std::to_string(clickCount));
    spriteText->setFillColor(sf::Color::White);
    spriteText->setCharacterSize(100);
    spriteText->setScale(sf::Vector2f(.1, .1)); // Fix blurry text

    uiTextEntity->spriteText = spriteText;

    universe->uiEntityManager->registerUIEntity(uiTextEntity);



    sge::UIEntity* uiButtonEntity = new sge::UIEntity{ new sf::Sprite() };
    uiButtonEntity->sprite->setTexture(*universe->assetsManager->getTextureSheet("button")->getTexture());
    uiButtonEntity->sprite->setTextureRect(universe->assetsManager->getTextureSheet("button")->getTextureRect(0));
    uiButtonEntity->sprite->setPosition(110, 60);

    sge::ClickableShape* clicakbleShape = new sge::ClickableShape(uiButtonEntity);
    clicakbleShape->action = [window, universe, &clickCount, uiTextEntity](sge::ClickableShape* thisClickableShape, sf::Event event){
        if(sge::isMouseOverClickableShape(thisClickableShape, window)){
            printf("Mouse over Button\n");
        }

        if(event.type == sf::Event::MouseButtonPressed){
            if(sge::isMouseOverClickableShape(thisClickableShape, window)){
                thisClickableShape->getOwnerUIEntity()->sprite->setTextureRect(universe->assetsManager->getTextureSheet("button")->getTextureRect(1));
            }
        }
        if(event.type == sf::Event::MouseButtonReleased){
            thisClickableShape->getOwnerUIEntity()->sprite->setTextureRect(universe->assetsManager->getTextureSheet("button")->getTextureRect(0));
            
            if(sge::isMouseOverClickableShape(thisClickableShape, window)){
                clickCount++;
                uiTextEntity->spriteText->setString(std::to_string(clickCount));
            }
        }
    };

    uiButtonEntity->clickableShape = clicakbleShape;

    universe->uiEntityManager->registerUIEntity(uiButtonEntity);



    universe->loop();

    return 0;
}