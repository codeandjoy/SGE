#include <vector>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "../../SGE.hpp"

void resetBall(sge::Entity* ball){
    ball->sprite->setPosition(sf::Vector2f(495, 345));    
    ball->motionUnit->velocity.x = 300;
    ball->motionUnit->velocity.y = 300;
}

class ScoreTextEntity : public sge::Entity{
    public:
        ScoreTextEntity(sf::Font* font, sf::Vector2f position){
            sprite = new sge::Sprite();
            sprite->setPosition(position);
            spriteText = new sge::SpriteText(sprite);
            spriteText->setFont(*font);
            spriteText->setString("0");
            spriteText->setFillColor(sf::Color(120, 120, 120));
            spriteText->setCharacterSize(100);
        }
};



class RacketBordersInteraction : public sge::CollisionInteraction{
    public: 
        RacketBordersInteraction(
            std::vector<std::string> initiatorGroups,
            std::vector<std::string> recipientGroups
        )
            : sge::CollisionInteraction(initiatorGroups, recipientGroups){}

        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }

        void continuousPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{ return sge::resolveAABB(collisions); }
};

class BounceInteraction : public sge::CollisionInteraction{
    public:
        BounceInteraction(
            std::vector<std::string> initiatorGroups,
            std::vector<std::string> recipientGroups
        )
            : sge::CollisionInteraction(initiatorGroups, recipientGroups){}
        
        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }

        void startPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            for(sge::Collision collision : collisions){
                sge::Entity* ballEntity = collision.initiator->getOwnerEntity();

                if(
                    collision.initiatorImpactSide == sge::CollisionSide::top ||
                    collision.initiatorImpactSide == sge::CollisionSide::bottom
                ){
                    ballEntity->motionUnit->velocity.y *= -1;
                }
                if(
                    collision.initiatorImpactSide == sge::CollisionSide::left ||
                    collision.initiatorImpactSide == sge::CollisionSide::right
                ){
                    ballEntity->motionUnit->velocity.x *= -1;
                }
            }
        }
};

class GoalInteraction : public sge::CollisionInteraction{
    public: 
        GoalInteraction(
            std::vector<std::string> initiatorGroups,
            std::vector<std::string> recipientGroups,
            int& p1Score,
            int& p2Score,
            sge::Entity* p1ScoreEntity,
            sge::Entity* p2ScoreEntity
        )
            : p1Score(p1Score),
              p2Score(p2Score),
              p1ScoreEntity(p1ScoreEntity), 
              p2ScoreEntity(p2ScoreEntity),
              sge::CollisionInteraction(initiatorGroups, recipientGroups){}

        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }

        void startPhaseCollisionResponse(std::vector<sge::Collision> collisions){
            for(sge::Collision collision : collisions){
                sge::Entity* ballEntity = collision.initiator->getOwnerEntity();

                if(ballEntity->motionUnit->velocity.y < 0){
                    p2Score += 1;
                    p2ScoreEntity->spriteText->setString(std::to_string(p2Score));
                    resetBall(ballEntity);
                }
                else if(ballEntity->motionUnit->velocity.y > 0){
                    p1Score += 1;
                    p1ScoreEntity->spriteText->setString(std::to_string(p1Score));
                    resetBall(ballEntity);
                }
            }
        }

    private:
        int& p1Score;
        int& p2Score;
        sge::Entity* p1ScoreEntity;
        sge::Entity* p2ScoreEntity;
};



class Racket1Controller : public sge::Controller{
    public: 
        Racket1Controller(sge::Entity* racketEntity) : racketEntityPtr(racketEntity){}
        
        void script(sf::Event event) override{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                racketEntityPtr->motionUnit->velocity.x = -400;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                racketEntityPtr->motionUnit->velocity.x = 400;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                racketEntityPtr->motionUnit->velocity.y = -400;
            }
            else{
                racketEntityPtr->motionUnit->velocity.x = 0;
            }
        }

    private:    
        sge::Entity* racketEntityPtr;
};
class Racket2Controller : public sge::Controller{
    public: 
        Racket2Controller(sge::Entity* racketEntity) : racketEntityPtr(racketEntity){}
        
        void script(sf::Event event) override{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                racketEntityPtr->motionUnit->velocity.x = -400;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                racketEntityPtr->motionUnit->velocity.x = 400;
            }
            else{
                racketEntityPtr->motionUnit->velocity.x = 0;
            }
        }

    private:    
        sge::Entity* racketEntityPtr;
};



int main(){
    int p1_score = 0;
    int p2_score = 0;



    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000, 700), "Pong");
    sf::View v = window->getDefaultView();
    sf::View* view = &v;

    sge::Universe* universe = new sge::Universe(window); 
    universe->setupDebugEntityManager();
    sge::AssetsManager* assetsManager = universe->assetsManager;
    sge::EntityManager* entityManager = universe->entityManager;
    sge::CollisionManager* collisionManager = universe->collisionManager;
    sge::DebugEntityManager* debugEntityManager = universe->debugEntityManager;
    sge::ControllerManager* controllerManager = universe-> controllerManager;



    assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/pong/assets/racket.png", "racket", sge::TextureSheetSizes{100, 10, 1, 1});
    assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/pong/assets/ball.png", "ball", sge::TextureSheetSizes{10, 10, 1, 1});
    assetsManager->loadFont(std::filesystem::current_path().string() + "/examples/pong/assets/m5x7.ttf", "m5x7");
 


    // UI
    sge::Entity* uiEntityP1Score = new ScoreTextEntity(
        universe->assetsManager->getFont("m5x7"),
        sf::Vector2f(485, 50)
    );
    
    sge::Entity* uiEntityP2Score = new ScoreTextEntity(
        universe->assetsManager->getFont("m5x7"),
        sf::Vector2f(485, 500)
    );

    entityManager->registerComponent(view, uiEntityP1Score);
    entityManager->registerComponent(view, uiEntityP2Score);
    //



    // World borders
    sge::CollisionShapeBorderSettings worldBorderSettings = { sf::Color::Red, 3 };

    sge::Entity* topBorderEntity = new sge::VoidEntity(
        sf::Vector2f(1000, 10),
        sf::Vector2f(0, 0),
        {"goal", "racket_borders"}
    );
    sge::DebugEntity* topBorderDebug = new sge::DebugEntity(topBorderEntity);
    topBorderDebug->customCollisionShapeBorderSettings["global_bounds"] = worldBorderSettings;
    entityManager->registerComponent(view, topBorderEntity);
    debugEntityManager->registerComponent(view, topBorderDebug);

    sge::Entity* bottomBorderEntity = new sge::VoidEntity(
        sf::Vector2f(1000, 10),
        sf::Vector2f(0, 690),
        {"goal"}
    );
    sge::DebugEntity* bottomBorderDebug = new sge::DebugEntity(bottomBorderEntity);
    bottomBorderDebug->customCollisionShapeBorderSettings["global_bounds"] = worldBorderSettings;
    entityManager->registerComponent(view, bottomBorderEntity);
    debugEntityManager->registerComponent(view, bottomBorderDebug);

    sge::Entity* leftBorderEntity = new sge::VoidEntity(
        sf::Vector2f(10, 700),
        sf::Vector2f(0, 0),
        {"racket_borders", "bouncy"}
    );
    sge::DebugEntity* leftBorderDebug = new sge::DebugEntity(leftBorderEntity);
    leftBorderDebug->customCollisionShapeBorderSettings["global_bounds"] = worldBorderSettings;
    entityManager->registerComponent(view, leftBorderEntity);
    debugEntityManager->registerComponent(view, leftBorderDebug);
    
    sge::Entity* rightBorderEntity = new sge::VoidEntity(
        sf::Vector2f(10, 700),
        sf::Vector2f(990, 0),
        {"racket_borders", "bouncy"}
    );
    sge::DebugEntity* rightBorderDebug = new sge::DebugEntity(rightBorderEntity);
    rightBorderDebug->customCollisionShapeBorderSettings["global_bounds"] = worldBorderSettings;
    entityManager->registerComponent(view, rightBorderEntity);
    debugEntityManager->registerComponent(view, rightBorderDebug);
    //



    // Game Entities
    sge::Entity* racket1Entity = new sge::SimpleMobileEntity(
        assetsManager->getTextureSheet("racket")->getTexture(),
        assetsManager->getTextureSheet("racket")->getTextureRect(0),
        sf::Vector2f(450, 30),
        {"racket", "bouncy"}
    );
    entityManager->registerComponent(view, racket1Entity);

    sge::Entity* racket2Entity = new sge::SimpleMobileEntity(
        assetsManager->getTextureSheet("racket")->getTexture(),
        assetsManager->getTextureSheet("racket")->getTextureRect(0),
        sf::Vector2f(450, 660),
        {"racket", "bouncy"}
    );
    entityManager->registerComponent(view, racket2Entity);

    sge::Entity* ballEntity = new sge::SimpleMobileEntity(
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


    
    // Interactions
    collisionManager->registerComponent(new RacketBordersInteraction({"racket"}, {"racket_borders"}));
    collisionManager->registerComponent(new BounceInteraction({"ball"}, {"bouncy"}));
    collisionManager->registerComponent(new GoalInteraction({"ball"}, {"goal"}, p1_score, p2_score, uiEntityP1Score, uiEntityP2Score));
    //



    // Racket controllers
    controllerManager->registerComponent(new Racket1Controller(racket1Entity));
    controllerManager->registerComponent(new Racket2Controller(racket2Entity));
    //



    universe->loop();
    return 0;
}