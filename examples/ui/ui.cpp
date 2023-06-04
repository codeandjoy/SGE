#include <filesystem>
#include <SFML/Graphics.hpp>

#include "../../SGE.hpp"


int main(){
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    sge::Universe* universe = new sge::Universe(window);

    sf::View v = window->getDefaultView();
    sf::View* view = &v;



    universe->assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/ui/assets/ButtonSpritesheet.png", "button", sge::TextureSheetSizes{32, 32, 1, 2});
    universe->assetsManager->loadFont(std::filesystem::current_path().string() + "/examples/ui/assets/m5x7.ttf", "m5x7");
    


    int clickCount = 0;



    sge::Scene* uiSceneText = new sge::Scene();

    sge::Entity* uiEntityText = new sge::Entity();
    uiEntityText->sprite = new sge::Sprite();
    uiEntityText->sprite->setPosition(424, 300);

    sge::SpriteText* uiAnotherSpriteText = new sge::SpriteText(uiEntityText->sprite);
    uiAnotherSpriteText->setFont(*universe->assetsManager->getFont("m5x7"));
    uiAnotherSpriteText->setString("Other UI screen");
    uiAnotherSpriteText->setFillColor(sf::Color::White);
    uiAnotherSpriteText->setCharacterSize(30);

    uiEntityText->spriteText = uiAnotherSpriteText;

    uiSceneText->registerEntity(view, uiEntityText);

    universe->layerSceneManager->registerComponent("text", uiSceneText);
    uiSceneText->hideSceneParts();



    sge::Scene* uiSceneButton = new sge::Scene();

    sge::Entity* uiEntityButtonText = new sge::Entity();
    uiEntityButtonText->sprite = new sge::Sprite();
    uiEntityButtonText->sprite->setPosition(484, 40);

    sge::SpriteText* spriteText = new sge::SpriteText(uiEntityButtonText->sprite);
    spriteText->setFont(*universe->assetsManager->getFont("m5x7"));
    spriteText->setString(std::to_string(clickCount));
    spriteText->setFillColor(sf::Color::White);
    spriteText->setCharacterSize(100);

    uiEntityButtonText->spriteText = spriteText;

    uiSceneButton->registerEntity(view, uiEntityButtonText);



    sge::Entity* uiEntityButton = new sge::Entity();
    uiEntityButton->sprite = new sge::Sprite(); 
    uiEntityButton->sprite->setScale(2,2);
    uiEntityButton->sprite->setTexture(*universe->assetsManager->getTextureSheet("button")->getTexture());
    uiEntityButton->sprite->setTextureRect(universe->assetsManager->getTextureSheet("button")->getTextureRect(0));
    uiEntityButton->sprite->setPosition(468, 200);

    sge::ClickableShape* clicakbleShape = new sge::ClickableShape(uiEntityButton);
    clicakbleShape->action = [window, universe, &clickCount, uiEntityButtonText, uiSceneText](sge::ClickableShape* thisClickableShape, sf::Event event){
        if(sge::isMouseOverClickableShape(thisClickableShape, window)){
            printf("Mouse over Button\n");
        }

        if(event.type == sf::Event::MouseButtonPressed){
            if(sge::isMouseOverClickableShape(thisClickableShape, window)){
                thisClickableShape->getOwnerEntity()->sprite->setTextureRect(universe->assetsManager->getTextureSheet("button")->getTextureRect(1));
            }
        }
        if(event.type == sf::Event::MouseButtonReleased){
            thisClickableShape->getOwnerEntity()->sprite->setTextureRect(universe->assetsManager->getTextureSheet("button")->getTextureRect(0));
            
            // Click count
            if(sge::isMouseOverClickableShape(thisClickableShape, window)){
                clickCount++;
                uiEntityButtonText->spriteText->setString(std::to_string(clickCount));
            }
            //

            // Toggle ui screen
            if(uiSceneText->isActive){
                uiSceneText->hideSceneParts();
            }
            else{
                uiSceneText->activateSceneParts();
            }
            //
        }
    };

    uiEntityButton->clickableShape = clicakbleShape;

    uiSceneButton->registerEntity(view, uiEntityButton);

    universe->layerSceneManager->registerComponent("button", uiSceneButton);



    universe->loop();

    return 0;
}