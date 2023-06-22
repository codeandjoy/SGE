#include <filesystem>
#include <SFML/Graphics.hpp>

#include "../../SGE.hpp"


class OtherUIScreenEntity : public sge::Entity{
    public:
        OtherUIScreenEntity(sf::Font* font){
            sprite = new sge::Sprite();
            sprite->setPosition(424, 300);

            spriteText = new sge::SpriteText(sprite);
            spriteText->setFont(*font);
            spriteText->setString("Other UI screen");
            spriteText->setFillColor(sf::Color::White);
            spriteText->setCharacterSize(30);
        }
};

class ClickCountEntity : public sge::Entity{
    public: 
        ClickCountEntity(sf::Font* font){
            sprite = new sge::Sprite();
            sprite->setPosition(484, 40);

            spriteText = new sge::SpriteText(sprite);
            spriteText->setFont(*font);
            spriteText->setString("0");
            spriteText->setFillColor(sf::Color::White);
            spriteText->setCharacterSize(100);
        }
};

class ClickButtonEntity : public sge::Entity{
    public:
        ClickButtonEntity(sf::Texture* texture, sf::IntRect textureRect){
            sprite = new sge::Sprite(); 
            sprite->setScale(2,2);
            sprite->setTexture(*texture);
            sprite->setTextureRect(textureRect);
            sprite->setPosition(468, 200);

            clickableShape = new sge::ClickableShape(this);
            // Action is setup outside, in main
        }
};

int main(){
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    sge::Universe* universe = new sge::Universe(window);

    sf::View v = window->getDefaultView();
    sf::View* view = &v;



    universe->assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/ui/assets/ButtonSpritesheet.png", "button", sge::TextureSheetSizes{32, 32, 1, 2});
    universe->assetsManager->loadFont(std::filesystem::current_path().string() + "/examples/ui/assets/m5x7.ttf", "m5x7");
    


    int clickCount = 0;



    // Other UI screen
    sge::Scene* otherUIScreenScene = new sge::Scene();

    otherUIScreenScene->addEntity(view, new OtherUIScreenEntity(universe->assetsManager->getFont("m5x7")));

    universe->layerSceneManager->registerComponent("text", otherUIScreenScene);
    otherUIScreenScene->hideSceneParts();
    //



    // Main UI screen
    sge::Scene* mainUIScreenScene = new sge::Scene();

    ClickCountEntity* clickCountEntity = new ClickCountEntity(universe->assetsManager->getFont("m5x7"));





    ClickButtonEntity* clickButtonEntity = new ClickButtonEntity(
        universe->assetsManager->getTextureSheet("button")->getTexture(),
        universe->assetsManager->getTextureSheet("button")->getTextureRect(0)
    );
    // Action is setup outside because of captures
    clickButtonEntity->clickableShape->action = [window, universe, &clickCount, clickCountEntity, otherUIScreenScene](sge::ClickableShape* thisClickableShape, sf::Event event){
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
                clickCountEntity->spriteText->setString(std::to_string(clickCount));
            }
            //

            // Toggle ui screen
            if(otherUIScreenScene->isActive){
                otherUIScreenScene->hideSceneParts();
            }
            else{
                otherUIScreenScene->activateSceneParts();
            }
            //
        }
    };



    mainUIScreenScene->addEntity(view, clickCountEntity);
    mainUIScreenScene->addEntity(view, clickButtonEntity);

    universe->layerSceneManager->registerComponent("button", mainUIScreenScene);



    universe->loop();

    return 0;
}