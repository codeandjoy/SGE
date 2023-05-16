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

    sge::Universe* universe = new sge::Universe(); 
    sge::UIEntityManager* uiEntityManager = universe->uiEntityManager;
    sge::AssetsManager* assetsManager = universe->assetsManager;
    sge::EntityManager* entityManager = universe->entityManager;
    sge::CollisionManager* collisionManager = universe->collisionManager;
    sge::DebugManager* debugManager = universe->debugManager;

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000, 700), "Pong");
    universe->setupWindow(window);
    


    assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/pong/assets/racket.png", "racket", sge::TextureSheetSizes{100, 10, 1, 1});
    assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/pong/assets/ball.png", "ball", sge::TextureSheetSizes{10, 10, 1, 1});
    assetsManager->loadFont(std::filesystem::current_path().string() + "/examples/pong/assets/m5x7.ttf", "m5x7");
 

    // UI
    sge::UIEntity* p1ScoreUIEntity = new sge::UIEntity{ new sf::Sprite() };
    p1ScoreUIEntity->sprite->setPosition(sf::Vector2f(485, 50));
    sge::SpriteText* p1SpriteText = new sge::SpriteText(p1ScoreUIEntity->sprite);
    p1SpriteText->setFont(*universe->assetsManager->getFont("m5x7"));
    p1SpriteText->setString(std::to_string(p1_score));
    p1SpriteText->setFillColor(sf::Color(120, 120, 120));
    p1SpriteText->setCharacterSize(100);
    p1ScoreUIEntity->spriteText = p1SpriteText;
    
    sge::UIEntity* p2ScoreUIEntity = new sge::UIEntity{ new sf::Sprite() };
    p2ScoreUIEntity->sprite->setPosition(sf::Vector2f(485, 500));
    sge::SpriteText* p2SpriteText = new sge::SpriteText(p2ScoreUIEntity->sprite);
    p2SpriteText->setFont(*universe->assetsManager->getFont("m5x7"));
    p2SpriteText->setString(std::to_string(p2_score));
    p2SpriteText->setFillColor(sf::Color(120, 120, 120));
    p2SpriteText->setCharacterSize(100);
    p2ScoreUIEntity->spriteText = p2SpriteText;

    uiEntityManager->registerUIEntity(p1ScoreUIEntity);
    uiEntityManager->registerUIEntity(p2ScoreUIEntity);
    //



    // World borders
    sge::CollisionShapeBorderSettings worldBorderSettings = { sf::Color::Red, 3 };

    sge::Entity* topBorderEntity = sge::buildVoidEntity(
        sf::Vector2f(1000, 10),
        sf::Vector2f(0, 0)
    );
    sge::DebugEntity* topBorderDebug = new sge::DebugEntity(topBorderEntity);
    topBorderDebug->customCollisionShapeBorderSettings["globalBounds"] = worldBorderSettings;
    entityManager->registerEntity(topBorderEntity);
    debugManager->registerDebugEntity(topBorderDebug);

    sge::Entity* bottomBorderEntity = sge::buildVoidEntity(
        sf::Vector2f(1000, 10),
        sf::Vector2f(0, 690)
    );
    sge::DebugEntity* bottomBorderDebug = new sge::DebugEntity(bottomBorderEntity);
    bottomBorderDebug->customCollisionShapeBorderSettings["globalBounds"] = worldBorderSettings;
    entityManager->registerEntity(bottomBorderEntity);
    debugManager->registerDebugEntity(bottomBorderDebug);

    sge::Entity* leftBorderEntity = sge::buildVoidEntity(
        sf::Vector2f(10, 700),
        sf::Vector2f(0, 0)
    );
    sge::DebugEntity* leftBorderDebug = new sge::DebugEntity(leftBorderEntity);
    leftBorderDebug->customCollisionShapeBorderSettings["globalBounds"] = worldBorderSettings;
    entityManager->registerEntity(leftBorderEntity);
    debugManager->registerDebugEntity(leftBorderDebug);
    
    sge::Entity* rightBorderEntity = sge::buildVoidEntity(
        sf::Vector2f(10, 700),
        sf::Vector2f(990, 0)
    );
    sge::DebugEntity* rightBorderDebug = new sge::DebugEntity(rightBorderEntity);
    rightBorderDebug->customCollisionShapeBorderSettings["globalBounds"] = worldBorderSettings;
    entityManager->registerEntity(rightBorderEntity);
    debugManager->registerDebugEntity(rightBorderDebug);
    //



    // Game Entities
    sge::Entity* racket1Entity = sge::buildMobileEntity(
        assetsManager->getTextureSheet("racket")->getTexture(),
        assetsManager->getTextureSheet("racket")->getTextureRect(0),
        sf::Vector2f(450, 30)
    );
    entityManager->registerEntity(racket1Entity);

    sge::Entity* racket2Entity = sge::buildMobileEntity(
        assetsManager->getTextureSheet("racket")->getTexture(),
        assetsManager->getTextureSheet("racket")->getTextureRect(0),
        sf::Vector2f(450, 660)
    );
    entityManager->registerEntity(racket2Entity);

    sge::Entity* ballEntity = sge::buildMobileEntity(
        assetsManager->getTextureSheet("ball")->getTexture(),
        assetsManager->getTextureSheet("ball")->getTextureRect(0),
        sf::Vector2f(495, 345)
    );
    entityManager->registerEntity(ballEntity);
    //



    // Game entity behaviours
    resetBall(ballEntity);
    //



    // Game object interactions
    std::vector<sge::CollisionShape*> racketsCollisionGroup{
        racket1Entity->collisionShapes["globalBounds"],
        racket2Entity->collisionShapes["globalBounds"]
    };
    std::vector<sge::CollisionShape*> racketBordersCollisionGroup{
        leftBorderEntity->collisionShapes["globalBounds"],
        rightBorderEntity->collisionShapes["globalBounds"]
    };
    std::vector<sge::CollisionShape*> ballCollisionGroup{ ballEntity->collisionShapes["globalBounds"] };
    std::vector<sge::CollisionShape*> bouncyCollisionGroup{
        racket1Entity->collisionShapes["globalBounds"],
        racket2Entity->collisionShapes["globalBounds"],
        leftBorderEntity->collisionShapes["globalBounds"],
        rightBorderEntity->collisionShapes["globalBounds"]
    };
    std::vector<sge::CollisionShape*> goalCollisionGroup{
        topBorderEntity->collisionShapes["globalBounds"],
        bottomBorderEntity->collisionShapes["globalBounds"]
    };
    collisionManager->registerCollisionGroup("racket", racketsCollisionGroup);
    collisionManager->registerCollisionGroup("racket_borders", racketBordersCollisionGroup);
    collisionManager->registerCollisionGroup("ball", ballCollisionGroup);
    collisionManager->registerCollisionGroup("bouncy", bouncyCollisionGroup);
    collisionManager->registerCollisionGroup("goal", goalCollisionGroup);

    sge::CollisionPair* racket_racket_borders = new sge::CollisionPair();
    racket_racket_borders->collisionGroups = std::make_pair("racket", "racket_borders");
    racket_racket_borders->algorithm = sge::boundingBox;
    racket_racket_borders->continuousPhaseCollisionResponse = sge::resolveAABB;
    sge::CollisionPair* ball_bouncy = new sge::CollisionPair();
    ball_bouncy->collisionGroups = std::make_pair("ball", "bouncy"); // TODO move to CollisionPari constructor
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
    sge::CollisionPair* ball_goal = new sge::CollisionPair();
    ball_goal->collisionGroups = std::make_pair("ball", "goal");
    ball_goal->algorithm = sge::boundingBox;
    ball_goal->startPhaseCollisionResponse = [&p1_score, &p2_score, ballEntity, p1ScoreUIEntity, p2ScoreUIEntity](std::vector<sge::Collision> collisions){
        for(sge::Collision collision : collisions){
            if(ballEntity->physicalObject->velocity.y < 0){
                p2_score += 1;
                p2ScoreUIEntity->spriteText->setString(std::to_string(p2_score));
                resetBall(ballEntity);
            }
            else if(ballEntity->physicalObject->velocity.y > 0){
                p1_score += 1;
                p1ScoreUIEntity->spriteText->setString(std::to_string(p1_score));
                resetBall(ballEntity);
            }
        }
    };
    collisionManager->registerCollisionPair("racket_racket_borders", racket_racket_borders);
    collisionManager->registerCollisionPair("ball_bouncy", ball_bouncy);
    collisionManager->registerCollisionPair("ball_goal", ball_goal);
    //



    universe->addController([racket1Entity](){
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
    universe->addController([racket2Entity](){
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