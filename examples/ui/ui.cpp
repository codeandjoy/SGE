#include <filesystem>
#include "../../SGE.hpp"


int main(){
    sge::Universe* universe = new sge::Universe();

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    
    universe->setupWindow(window);



    universe->assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/ui/assets/ButtonSpritesheet.png", "button", sge::TextureSheetSizes{32, 32, 1, 2});
    universe->assetsManager->loadFont(std::filesystem::current_path().string() + "/examples/ui/assets/m5x7.ttf", "m5x7");
    


    int clickCount = 0;



    sge::UIScreen* hiddenUIScreen = new sge::UIScreen();

    sge::UIEntity* uiAnotherTextEntity = new sge::UIEntity{ new sf::Sprite() };
    uiAnotherTextEntity->sprite->setPosition(424, 300);

    sge::SpriteText* uiAnotherSpriteText = new sge::SpriteText(uiAnotherTextEntity->sprite);
    uiAnotherSpriteText->setFont(*universe->assetsManager->getFont("m5x7"));
    uiAnotherSpriteText->setString("Other UI screen");
    uiAnotherSpriteText->setFillColor(sf::Color::White);
    uiAnotherSpriteText->setCharacterSize(30);

    uiAnotherTextEntity->spriteText = uiAnotherSpriteText;

    hiddenUIScreen->addUIEntity(uiAnotherTextEntity);

    universe->uiScreenManager->registerUIScreen("hidden", hiddenUIScreen);
    universe->uiScreenManager->hideUIScreen("hidden");



    sge::UIScreen* buttonScreen = new sge::UIScreen();

    sge::UIEntity* uiTextEntity = new sge::UIEntity{ new sf::Sprite() };
    uiTextEntity->sprite->setPosition(484, 40);

    sge::SpriteText* spriteText = new sge::SpriteText(uiTextEntity->sprite);
    spriteText->setFont(*universe->assetsManager->getFont("m5x7"));
    spriteText->setString(std::to_string(clickCount));
    spriteText->setFillColor(sf::Color::White);
    spriteText->setCharacterSize(100);

    uiTextEntity->spriteText = spriteText;

    buttonScreen->addUIEntity(uiTextEntity);



    sge::UIEntity* uiButtonEntity = new sge::UIEntity{ new sf::Sprite() };
    uiButtonEntity->sprite->setScale(2,2);
    uiButtonEntity->sprite->setTexture(*universe->assetsManager->getTextureSheet("button")->getTexture());
    uiButtonEntity->sprite->setTextureRect(universe->assetsManager->getTextureSheet("button")->getTextureRect(0));
    uiButtonEntity->sprite->setPosition(468, 200);

    sge::ClickableShape* clicakbleShape = new sge::ClickableShape(uiButtonEntity);
    clicakbleShape->action = [window, universe, &clickCount, uiTextEntity, hiddenUIScreen](sge::ClickableShape* thisClickableShape, sf::Event event){
        
        
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
            
            // Click count
            if(sge::isMouseOverClickableShape(thisClickableShape, window)){
                clickCount++;
                uiTextEntity->spriteText->setString(std::to_string(clickCount));
            }
            //

            // Toggle ui screen
            if(!hiddenUIScreen->isVisible){
                universe->uiScreenManager->showUIScreen("hidden");
            }
            else{
                universe->uiScreenManager->hideUIScreen("hidden");
            }
            //
        }
    };

    uiButtonEntity->clickableShape = clicakbleShape;

    buttonScreen->addUIEntity(uiButtonEntity);

    universe->uiScreenManager->registerUIScreen("buttonScreen", buttonScreen);



    universe->loop();

    return 0;
}