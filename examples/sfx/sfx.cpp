#include <filesystem>
#include "../../SGE.hpp"


int main(){
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    sf::View v = window->getDefaultView();
    sf::View* view = &v;

    sge::Universe* universe = new sge::Universe(window);
    sge::AssetsManager* assetsManager = universe->assetsManager;
    sge::EntityManager* entityManager = universe->entityManager;


    
    assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/sfx/assets/ButtonSpritesheet.png", "button", sge::TextureSheetSizes{32, 32, 1, 2});
    assetsManager->loadSFX(std::filesystem::current_path().string() + "/examples/sfx/assets/sfx.wav", "swordSwing");
    assetsManager->specifyMusicLocation(std::filesystem::current_path().string() + "/examples/sfx/assets/music.wav", "battleMusic");


    sf::Music* music = new sf::Music();
    music->openFromFile(assetsManager->getMusicLocation("battleMusic"));
  

    sge::Entity* uiSFXButton = new sge::Entity();
    uiSFXButton->sprite = new sge::Sprite();
    uiSFXButton->sprite->setScale(2,2);
    uiSFXButton->sprite->setTexture(*assetsManager->getTextureSheet("button")->getTexture());
    uiSFXButton->sprite->setTextureRect(assetsManager->getTextureSheet("button")->getTextureRect(0));
    uiSFXButton->sprite->setPosition(468, 200);
    sge::ClickableShape* clicakbleShapeSFX = new sge::ClickableShape(uiSFXButton);
    clicakbleShapeSFX->action = [assetsManager, window](sge::ClickableShape* thisClickableShape, sf::Event event){
        if(event.type == sf::Event::MouseButtonReleased){
            if(sge::isMouseOverClickableShape(thisClickableShape, window)){
                assetsManager->getSound("swordSwing")->play();
            }
        }
    };
    uiSFXButton->clickableShape = clicakbleShapeSFX;

    sge::Entity* uiMusicButton = new sge::Entity();
    uiMusicButton->sprite = new sge::Sprite();
    uiMusicButton->sprite->setScale(2,2);
    uiMusicButton->sprite->setTexture(*assetsManager->getTextureSheet("button")->getTexture());
    uiMusicButton->sprite->setTextureRect(assetsManager->getTextureSheet("button")->getTextureRect(0));
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


    entityManager->registerComponent(view, uiSFXButton);
    entityManager->registerComponent(view, uiMusicButton);

    universe->loop();

    return 0;
}