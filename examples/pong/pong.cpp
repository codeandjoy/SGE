#include <vector>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "../../SGE.hpp"


void resetBall(sge::Entity* ball){
    ball->sprite->setPosition(sf::Vector2f(495, 345));    
    ball->physicalObject->velocity.x = 300;
    ball->physicalObject->velocity.y = 300;
}

int main(){
    int p1_score = 0;
    int p2_score = 0;



    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000, 700), "Pong");
    sf::View v = window->getDefaultView();
    sf::View* view = &v;

    sge::Universe* universe = new sge::Universe(window); 
    universe->setupDebug();
    sge::AssetsManager* assetsManager = universe->assetsManager;
    sge::EntityManager* entityManager = universe->entityManager;
    sge::CollisionManager* collisionManager = universe->collisionManager;
    sge::DebugManager* debugManager = universe->debugManager;

    


    assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/pong/assets/racket.png", "racket", sge::TextureSheetSizes{100, 10, 1, 1});
    assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/pong/assets/ball.png", "ball", sge::TextureSheetSizes{10, 10, 1, 1});
    assetsManager->loadFont(std::filesystem::current_path().string() + "/examples/pong/assets/m5x7.ttf", "m5x7");
 

    // UI
    sge::Entity* uiEntityP1Score = new sge::Entity();
    uiEntityP1Score->sprite = new sge::Sprite();
    uiEntityP1Score->sprite->setPosition(sf::Vector2f(485, 50));
    sge::SpriteText* p1SpriteText = new sge::SpriteText(uiEntityP1Score->sprite);
    p1SpriteText->setFont(*universe->assetsManager->getFont("m5x7"));
    p1SpriteText->setString(std::to_string(p1_score));
    p1SpriteText->setFillColor(sf::Color(120, 120, 120));
    p1SpriteText->setCharacterSize(100);
    uiEntityP1Score->spriteText = p1SpriteText;
    
    sge::Entity* uiEntityP2Score = new sge::Entity();
    uiEntityP2Score->sprite = new sge::Sprite();
    uiEntityP2Score->sprite->setPosition(sf::Vector2f(485, 500));
    sge::SpriteText* p2SpriteText = new sge::SpriteText(uiEntityP2Score->sprite);
    p2SpriteText->setFont(*universe->assetsManager->getFont("m5x7"));
    p2SpriteText->setString(std::to_string(p2_score));
    p2SpriteText->setFillColor(sf::Color(120, 120, 120));
    p2SpriteText->setCharacterSize(100);
    uiEntityP2Score->spriteText = p2SpriteText;

    entityManager->registerComponent(view, uiEntityP1Score);
    entityManager->registerComponent(view, uiEntityP2Score);
    //



    // World borders
    sge::CollisionShapeBorderSettings worldBorderSettings = { sf::Color::Red, 3 };

    sge::Entity* topBorderEntity = sge::buildVoidEntity(
        sf::Vector2f(1000, 10),
        sf::Vector2f(0, 0),
        {"goal"}
    );
    sge::DebugEntity* topBorderDebug = new sge::DebugEntity(topBorderEntity);
    topBorderDebug->customCollisionShapeBorderSettings["globalBounds"] = worldBorderSettings;
    entityManager->registerComponent(view, topBorderEntity);
    debugManager->registerComponent(view, topBorderDebug);

    sge::Entity* bottomBorderEntity = sge::buildVoidEntity(
        sf::Vector2f(1000, 10),
        sf::Vector2f(0, 690),
        {"goal"}
    );
    sge::DebugEntity* bottomBorderDebug = new sge::DebugEntity(bottomBorderEntity);
    bottomBorderDebug->customCollisionShapeBorderSettings["globalBounds"] = worldBorderSettings;
    entityManager->registerComponent(view, bottomBorderEntity);
    debugManager->registerComponent(view, bottomBorderDebug);

    sge::Entity* leftBorderEntity = sge::buildVoidEntity(
        sf::Vector2f(10, 700),
        sf::Vector2f(0, 0),
        {"racket_borders", "bouncy"}
    );
    sge::DebugEntity* leftBorderDebug = new sge::DebugEntity(leftBorderEntity);
    leftBorderDebug->customCollisionShapeBorderSettings["globalBounds"] = worldBorderSettings;
    entityManager->registerComponent(view, leftBorderEntity);
    debugManager->registerComponent(view, leftBorderDebug);
    
    sge::Entity* rightBorderEntity = sge::buildVoidEntity(
        sf::Vector2f(10, 700),
        sf::Vector2f(990, 0),
        {"racket_borders", "bouncy"}
    );
    sge::DebugEntity* rightBorderDebug = new sge::DebugEntity(rightBorderEntity);
    rightBorderDebug->customCollisionShapeBorderSettings["globalBounds"] = worldBorderSettings;
    entityManager->registerComponent(view, rightBorderEntity);
    debugManager->registerComponent(view, rightBorderDebug);
    //



    // Game Entities
    sge::Entity* racket1Entity = sge::buildMobileEntity(
        assetsManager->getTextureSheet("racket")->getTexture(),
        assetsManager->getTextureSheet("racket")->getTextureRect(0),
        sf::Vector2f(450, 30),
        {"racket", "bouncy"}
    );
    entityManager->registerComponent(view, racket1Entity);

    sge::Entity* racket2Entity = sge::buildMobileEntity(
        assetsManager->getTextureSheet("racket")->getTexture(),
        assetsManager->getTextureSheet("racket")->getTextureRect(0),
        sf::Vector2f(450, 660),
        {"racket", "bouncy"}
    );
    entityManager->registerComponent(view, racket2Entity);

    sge::Entity* ballEntity = sge::buildMobileEntity(
        assetsManager->getTextureSheet("ball")->getTexture(),
        assetsManager->getTextureSheet("ball")->getTextureRect(0),
        sf::Vector2f(495, 345),
        {"ball"}
    );
    entityManager->registerComponent(view, ballEntity);
    //



    // Game entity behaviours
    resetBall(ballEntity);
    //



    // Game object interactions
    sge::CollisionPair* racket_racket_borders = new sge::CollisionPair{ "racket", "racket_borders" };
    racket_racket_borders->algorithm = sge::boundingBox;
    racket_racket_borders->continuousPhaseCollisionResponse = sge::resolveAABB;
    sge::CollisionPair* ball_bouncy = new sge::CollisionPair{ "ball", "bouncy" };
    ball_bouncy->algorithm = sge::boundingBox;
    ball_bouncy->startPhaseCollisionResponse = [ballEntity](std::vector<sge::Collision> collisions){
        for(sge::Collision collision : collisions){
            if(
                collision.initiatorImpactSide == sge::CollisionSide::top ||
                collision.initiatorImpactSide == sge::CollisionSide::bottom
            ){
                ballEntity->physicalObject->velocity.y *= -1;
            }
            if(
                collision.initiatorImpactSide == sge::CollisionSide::left ||
                collision.initiatorImpactSide == sge::CollisionSide::right
            ){
                ballEntity->physicalObject->velocity.x *= -1;
            }
        }
    };
    sge::CollisionPair* ball_goal = new sge::CollisionPair{ "ball", "goal" };
    ball_goal->algorithm = sge::boundingBox;
    ball_goal->startPhaseCollisionResponse = [&p1_score, &p2_score, ballEntity, uiEntityP1Score, uiEntityP2Score](std::vector<sge::Collision> collisions){
        for(sge::Collision collision : collisions){
            if(ballEntity->physicalObject->velocity.y < 0){
                p2_score += 1;
                uiEntityP2Score->spriteText->setString(std::to_string(p2_score));
                resetBall(ballEntity);
            }
            else if(ballEntity->physicalObject->velocity.y > 0){
                p1_score += 1;
                uiEntityP1Score->spriteText->setString(std::to_string(p1_score));
                resetBall(ballEntity);
            }
        }
    };
    collisionManager->registerCollisionPair("racket_racket_borders", racket_racket_borders);
    collisionManager->registerCollisionPair("ball_bouncy", ball_bouncy);
    collisionManager->registerCollisionPair("ball_goal", ball_goal);
    //



    universe->controllerManager->registerComponent([racket1Entity](auto _){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            racket1Entity->physicalObject->velocity.x = -400;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            racket1Entity->physicalObject->velocity.x = 400;
        }
        else{
            racket1Entity->physicalObject->velocity.x = 0;
        }
    });
    universe->controllerManager->registerComponent([racket2Entity](auto _){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            racket2Entity->physicalObject->velocity.x = -400;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            racket2Entity->physicalObject->velocity.x = 400;
        }
        else{
            racket2Entity->physicalObject->velocity.x = 0;
        }
    });



    universe->loop();
    return 0;
}