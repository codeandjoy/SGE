#include <stdio.h>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

#include "../../SGE.hpp"


class AABBInteraction : public sge::CollisionInteraction{
    public:
        AABBInteraction(std::vector<std::string> initiatorGroups, std::vector<std::string> recipientGroups) : sge::CollisionInteraction(initiatorGroups, recipientGroups){};

        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }
    
        void startPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            printf("star_phase\n");            
        }

        void continuousPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            sge::resolveAABB(collisions);
            sge::initiatorStandOnTopOfRecipient(collisions);
        }

        void endPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            printf("end_phase\n");            
        }
};

class PushInteraction : public sge::CollisionInteraction{
    public:
        PushInteraction(std::vector<std::string> initiatorGroups, std::vector<std::string> recipientGroups, sge::DebugEntity* boxDE) : sge::CollisionInteraction(initiatorGroups, recipientGroups), boxDE(boxDE){};

        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }
    
        void startPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            boxDE->customCollisionShapeBorderSettings["global_bounds"] = sge::CollisionShapeBorderSettings{sf::Color::Red};

            for(sge::Collision collision : collisions){
                if(collision.recipientImpactSide == sge::CollisionSide::right){
                    collision.recipient->getOwnerEntity()->physicalObject->velocity.x = -10;
                }
                else if(collision.recipientImpactSide == sge::CollisionSide::left){
                    collision.recipient->getOwnerEntity()->physicalObject->velocity.x = 10;
                }
            }            
        }

        void endPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            boxDE->customCollisionShapeBorderSettings["global_bounds"] = sge::CollisionShapeBorderSettings{sf::Color::Green};
        
            for(sge::Collision collision : collisions){
                collision.recipient->getOwnerEntity()->physicalObject->velocity.x = 0;
            }          
        }
    
    private:
        sge::DebugEntity* boxDE;
};



class CameraView : public sge::ScriptedView{
    public:
        CameraView(sge::Entity* playerEntity) : m_playerEntityPtr(playerEntity){
            this->setCenter(sf::Vector2f(100, 100));
            this->setSize(sf::Vector2f(500, 300));
        };

        void script(){
            sf::Vector2f center = m_playerEntityPtr->sprite->getPosition();
            center.x += 4;
            center.y += 4;

            m_scroll.x = center.x - this->getCenter().x - m_scroll.x / 100;
            m_scroll.y = center.y - this->getCenter().y - m_scroll.y / 100;
            
            this->setCenter(center - m_scroll);
        }
    private:
        sf::Vector2f m_scroll = sf::Vector2f(0, 0);
        sge::Entity* m_playerEntityPtr;
};



class GravityEntity : public sge::MobileEntity{
    public :
        GravityEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups)
            : sge::MobileEntity(texture, textureRect, position, collisionGroups){
                physicalObject->acceleration.y = .4; // Gravity
        }
};

class PlayerEntity : public GravityEntity{
    public:
        PlayerEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups, sge::TextureSheet* animationTextureSheet)
            : GravityEntity(texture, textureRect, position, collisionGroups){
                animationCluster = new sge::AnimationCluster(sprite);
                animationCluster->animationDelayMilliseconds = 80;
                animationCluster->addTextureSequence("idle", new sge::TextureSequence(std::vector<int>{260}, animationTextureSheet));
                animationCluster->addTextureSequence("runRight", new sge::TextureSequence(std::vector<int>{262, 263, 264}, animationTextureSheet));
                animationCluster->addTextureSequence("runLeft", new sge::TextureSequence(std::vector<int>{262, 263, 264}, animationTextureSheet, true));
                animationCluster->setCurrentTextureSequence("idle");

                collisionShapes["global_bounds"]->setSize(sf::Vector2f(16, 8));
                collisionShapes["global_bounds"]->offset = sf::Vector2f(0, 8);
            }
};



class KeyboardController : public sge::Controller{
    public:
        KeyboardController(sge::Entity* playerEntity) : m_playerEntityPtr(playerEntity){}; 

        void script(sf::Event event) override{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                m_playerEntityPtr->physicalObject->velocity.x = -100;
                m_playerEntityPtr->animationCluster->setCurrentTextureSequence("runLeft");
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                m_playerEntityPtr->physicalObject->velocity.x = 100;
                m_playerEntityPtr->animationCluster->setCurrentTextureSequence("runRight");
            }
            else{
                m_playerEntityPtr->physicalObject->velocity.x = 0;
                m_playerEntityPtr->animationCluster->setCurrentTextureSequence("idle");
            }

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
                m_playerEntityPtr->physicalObject->velocity.y = -200;
            }
        }

    private:
        sge::Entity* m_playerEntityPtr;
};


int main(){
    printf(".▄▄ ·  ▄▄ • ▄▄▄ .\n▐█ ▀. ▐█ ▀ ▪▀▄.▀·\n▄▀▀▀█▄▄█ ▀█▄▐▀▀▪▄\n▐█▄▪▐█▐█▄▪▐█▐█▄▄▌\n ▀▀▀▀ ·▀▀▀▀  ▀▀▀ \n");



    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    window->setKeyRepeatEnabled(false); // For proper keyboard events handling (e.g. jumping)

    sge::Universe* universe = new sge::Universe(window);
    universe->setupDebug();



    // Load all textures
    universe->assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/dev/assets/tilemap.png", "tileset", sge::TextureSheetSizes{16, 16, 20, 20});
    //



    // Player
    PlayerEntity* playerEntity = new PlayerEntity(
        universe->assetsManager->getTextureSheet("tileset")->getTexture(),
        universe->assetsManager->getTextureSheet("tileset")->getTextureRect(260),
        sf::Vector2f(200, 100),
        {"player"},
        universe->assetsManager->getTextureSheet("tileset")
    );

    sge::DebugEntity* playerDE = new sge::DebugEntity(playerEntity);
    playerDE->customCollisionShapeBorderSettings["global_bounds"] = sge::CollisionShapeBorderSettings{sf::Color::Red};
    // Extra debug function example
    // playerDE->addExtraDebugFunction([playerEntity](auto _){
    //     printf("%f, %f\n", playerEntity->getPosition().x, playerEntity->getPosition().y);
    // });
    //



    // Read map
    tmx::Map map;
    if(!map.load(std::filesystem::current_path().string() + "/examples/dev/assets/test_map.tmx")){
        printf("Can't load map");
        exit(1);
    }

    const auto& layers = map.getLayers();
    const auto& tiles = layers[0]->getLayerAs<tmx::TileLayer>().getTiles();
    const auto& boxes = layers[1]->getLayerAs<tmx::ObjectGroup>().getObjects();
    //

    // Tile layer
    std::vector<sge::Entity*> mapTileEntities;

    for(int i = 0; i < map.getTileCount().y; i++){
        for(int j = 0; j < map.getTileCount().x; j++){
            if(tiles[map.getTileCount().x*i+j].ID != 0){
                mapTileEntities.push_back(new sge::StaticEntity(
                    universe->assetsManager->getTextureSheet("tileset")->getTexture(),
                    universe->assetsManager->getTextureSheet("tileset")->getTextureRect(tiles[map.getTileCount().x*i+j].ID-1),
                    sf::Vector2f(j*map.getTileSize().x, i*map.getTileSize().y),
                    {"tiles"}
                ));
            }
        }
    }
    //

    // Object layer
    auto& box = boxes[0];

    GravityEntity* boxEntity = new GravityEntity(
        universe->assetsManager->getTextureSheet("tileset")->getTexture(),
        universe->assetsManager->getTextureSheet("tileset")->getTextureRect(box.getTileID()-1),
        sf::Vector2f(box.getPosition().x, box.getPosition().y),
        {"box"}
    );

    sge::DebugEntity* boxDE = new sge::DebugEntity(boxEntity);
    boxDE->customCollisionShapeBorderSettings["global_bounds"] = sge::CollisionShapeBorderSettings{sf::Color::Green};
    //
    


    CameraView* cameraView = new CameraView(playerEntity);



    universe->scriptedViewManager->registerComponent(cameraView);

    universe->entityManager->registerComponent(cameraView, playerEntity);
    universe->debugManager->registerComponent(cameraView, playerDE);

    universe->entityManager->registerComponent(cameraView, boxEntity);
    universe->debugManager->registerComponent(cameraView, boxDE);

    for(sge::Entity* entity : mapTileEntities){
        universe->entityManager->registerComponent(cameraView, entity);
    }



    // * Notes:
    // ! The collision shape CAN NOT be the initiator AND the recepient of the AABB response
    // ! To work properly, all AABB recipients with common initiator should be put together
    universe->collisionManager->registerComponent(new AABBInteraction({"player"}, {"tiles", "box"}));
    universe->collisionManager->registerComponent(new AABBInteraction({"box"}, {"tiles"}));
    universe->collisionManager->registerComponent(new PushInteraction({"player"}, {"box"}, boxDE));



    universe->controllerManager->registerComponent(new KeyboardController(playerEntity));



    universe->loop();

    return 0;
}