#include <SFML/Graphics.hpp>
#include <filesystem>

#include "../../SGE.hpp"


class WalkingLeft : public sge::State{
    public:
        WalkingLeft(sge::Entity* entity) : sge::State(entity){};

        void enterScript() override{
            m_walkClock->restart();
        }

        void updateScript(float dt, sge::StateCluster* containerStateCluster) override{
            if(m_walkClock->getElapsedTime().asSeconds() >= 1){
                m_walkClock->restart();
                containerStateCluster->setCurrentState("walking_right");
            }

            sf::Vector2f currentPosition = m_ownerEntityPtr->sprite->getPosition();
            m_ownerEntityPtr->sprite->setPosition(sf::Vector2f(currentPosition.x-100*dt, currentPosition.y));
        }

    private:
        sf::Clock* m_walkClock = new sf::Clock();
};

class WalkingRight : public sge::State{
    public:
        WalkingRight(sge::Entity* entity) : sge::State(entity){};

        void enterScript() override{
            m_walkClock->restart();
        }

        void updateScript(float dt, sge::StateCluster* containerStateCluster) override{
            if(m_walkClock->getElapsedTime().asSeconds() >= 1){
                m_walkClock->restart();
                containerStateCluster->setCurrentState("walking_left");
            }

            sf::Vector2f currentPosition = m_ownerEntityPtr->sprite->getPosition();
            m_ownerEntityPtr->sprite->setPosition(sf::Vector2f(currentPosition.x+100*dt, currentPosition.y));
        }

    private:
        sf::Clock* m_walkClock = new sf::Clock();
};

int main(){
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000, 600), "State");

    sf::View* dummyView = new sf::View(sf::Vector2f(100, 100), sf::Vector2f(250, 150)); 

    sge::Universe* universe = new sge::Universe(window);
    sge::EntityManager* entityManager = universe->entityManager;
    sge::AssetsManager* assetsManager = universe->assetsManager;



    universe->assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/state/assets/pico_8_knight_sprite.png", "knight", sge::TextureSheetSizes{8, 8, 12, 12});



    sge::Entity* entity = new sge::Entity();
    entity->sprite = new sge::Sprite();
    entity->sprite->setPosition(sf::Vector2f(100, 100));
    entity->sprite->setTexture(*assetsManager->getTextureSheet("knight")->getTexture());
    entity->sprite->setTextureRect(assetsManager->getTextureSheet("knight")->getTextureRect(9));
    
    WalkingLeft* walkingLeftEntityState = new WalkingLeft(entity);
    WalkingRight* walkingRightEntityState = new WalkingRight(entity);
    sge::StateCluster* entityStateCluster = new sge::StateCluster();
    entityStateCluster->states["walking_right"] = walkingRightEntityState;
    entityStateCluster->states["walking_left"] = walkingLeftEntityState;
    entityStateCluster->setCurrentState("walking_left"); // Setting start state

    entity->stateCluster = entityStateCluster;

    entityManager->registerComponent(dummyView, entity);



    universe->loop();

    return 0;
}