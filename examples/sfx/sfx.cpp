#include <filesystem>
#include "../../SGE.hpp"


int main(){
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");

    sge::Universe* universe = new sge::Universe();
    sge::AssetsManager* assetsManager = universe->assetsManager;

    universe->setupWindow(window);

    
    universe->assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/sfx/assets/ButtonSpritesheet.png", "button", sge::TextureSheetSizes{32, 32, 1, 2});
    universe->assetsManager->loadSFX(std::filesystem::current_path().string() + "/examples/sfx/assets/sfx.wav", "swordSwing");
    universe->assetsManager->specifyMusicLocation(std::filesystem::current_path().string() + "/examples/sfx/assets/music.wav", "battleMusic");


    sf::Music* music = new sf::Music();
    music->openFromFile(universe->assetsManager->getMusicLocation("battleMusic"));
  

    sge::UIEntity* uiSFXButton = new sge::UIEntity{ new sf::Sprite() };
    uiSFXButton->sprite->setScale(2,2);
    uiSFXButton->sprite->setTexture(*universe->assetsManager->getTextureSheet("button")->getTexture());
    uiSFXButton->sprite->setTextureRect(universe->assetsManager->getTextureSheet("button")->getTextureRect(0));
    uiSFXButton->sprite->setPosition(468, 200);
    sge::ClickableShape* clicakbleShapeSFX = new sge::ClickableShape(uiSFXButton);
    clicakbleShapeSFX->action = [universe, window](sge::ClickableShape* thisClickableShape, sf::Event event){
        if(event.type == sf::Event::MouseButtonReleased){
            if(sge::isMouseOverClickableShape(thisClickableShape, window)){
                universe->assetsManager->getSound("swordSwing")->play();
            }
        }
    };
    uiSFXButton->clickableShape = clicakbleShapeSFX;

    sge::UIEntity* uiMusicButton = new sge::UIEntity{ new sf::Sprite() };
    uiMusicButton->sprite->setScale(2,2);
    uiMusicButton->sprite->setTexture(*universe->assetsManager->getTextureSheet("button")->getTexture());
    uiMusicButton->sprite->setTextureRect(universe->assetsManager->getTextureSheet("button")->getTextureRect(0));
    uiMusicButton->sprite->setPosition(468, 300);
    sge::ClickableShape* clicakbleShapeMusic = new sge::ClickableShape(uiMusicButton);
    clicakbleShapeMusic->action = [&music, window](sge::ClickableShape* thisClickableShape, sf::Event event){
        if(event.type == sf::Event::MouseButtonReleased){
            if(sge::isMouseOverClickableShape(thisClickableShape, window)){
                if(music->getStatus() == sf::SoundSource::Status::Stopped ||
                   music->getStatus() == sf::SoundSource::Status::Paused
                ){
                    music->play();
                }
                else{
                    music->pause();
                }
            }
        }
    };
    uiMusicButton->clickableShape = clicakbleShapeMusic;


    universe->uiEntityManager->registerUIEntity(uiSFXButton);
    universe->uiEntityManager->registerUIEntity(uiMusicButton);

    universe->loop();

    return 0;
}