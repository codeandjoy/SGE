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
            // printf("star_phase\n");            
        }

        void continuousPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            sge::resolveAABB(collisions);
            sge::initiatorStandOnTopOfRecipient(collisions);
        }

        void endPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            // printf("end_phase\n");            
        }
};

class PlayerSurfaceInteraction : public sge::CollisionInteraction{
    public:
        PlayerSurfaceInteraction(std::vector<std::string> initiatorGroups, std::vector<std::string> recipientGroups) : sge::CollisionInteraction(initiatorGroups, recipientGroups){};

        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }
    
        void startPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            sge::StateCluster* playerStateCluster = collisions[0].initiator->getOwnerEntity()->stateCluster;
            
            playerStateCluster->deactivateState("jump");
            playerStateCluster->activateState("on_ground");
        }
};

class BoxSurfaceInteraction : public sge::CollisionInteraction{
    public:
        BoxSurfaceInteraction(std::vector<std::string> initiatorGroups, std::vector<std::string> recipientGroups) : sge::CollisionInteraction(initiatorGroups, recipientGroups){};

        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }
    
        void continuousPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            sge::MotionUnit* boxMotionUnit = collisions[0].initiator->getOwnerEntity()->motionUnit;

            if(boxMotionUnit->velocity.x){
                if(boxMotionUnit->velocity.x > 0){
                    boxMotionUnit->contactForces["kinetic_friction"] = sf::Vector2f(-200, 0);
                }
                else if(boxMotionUnit->velocity.x < 0){
                    boxMotionUnit->contactForces["kinetic_friction"] = sf::Vector2f(200, 0);
                }
            }
            else if(!boxMotionUnit->velocity.x){
                boxMotionUnit->contactForces.erase("kinetic_friction");
                // static friction (irrelevant atm)
            }
        }

        void endPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            sge::MotionUnit* boxMotionUnit = collisions[0].initiator->getOwnerEntity()->motionUnit;

            boxMotionUnit->contactForces.erase("kinetic_friction");
        }
};

class PushInteraction : public sge::CollisionInteraction{
    public:
        PushInteraction(std::vector<std::string> initiatorGroups, std::vector<std::string> recipientGroups, sge::DebugEntity* boxDE) : sge::CollisionInteraction(initiatorGroups, recipientGroups), boxDE(boxDE){};

        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }
    
        void startPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            printf("start\n");

            boxDE->customCollisionShapeBorderSettings["global_bounds"] = sge::CollisionShapeBorderSettings{sf::Color::Red};

            for(sge::Collision collision : collisions){
                if(collision.recipientImpactSide == sge::CollisionSide::right){
                    // collision.recipient->getOwnerEntity()->motionUnit->velocity.x = -30;
                    collision.recipient->getOwnerEntity()->motionUnit->contactForces["push"] = sf::Vector2f(-300, 0);
                }
                else if(collision.recipientImpactSide == sge::CollisionSide::left){
                    collision.recipient->getOwnerEntity()->motionUnit->contactForces["push"] = sf::Vector2f(300, 0);
                }

                for(auto& [name, _] : collision.recipient->getOwnerEntity()->motionUnit->contactForces){
                    printf("%s\n", name.c_str());
                }        
            }    

        }

        void endPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            printf("end\n");

            boxDE->customCollisionShapeBorderSettings["global_bounds"] = sge::CollisionShapeBorderSettings{sf::Color::Green};
        
            for(sge::Collision collision : collisions){
                collision.recipient->getOwnerEntity()->motionUnit->contactForces.erase("push");

                for(auto& [name, _] : collision.recipient->getOwnerEntity()->motionUnit->contactForces){
                    printf("endfoces:\n");
                    printf("%s\n", name.c_str());
                }
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



class PlayerMovingRightState : public sge::State{
    public:
        PlayerMovingRightState(sge::Entity* playerEntity) : sge::State(playerEntity){};

        void enterScript() override{
            m_ownerEntityPtr->motionUnit->velocity.x = 100;
        }

        void updateScript(float dt) override{
            if(m_ownerEntityPtr->stateCluster->isStateActive("on_ground")){
                if(m_ownerEntityPtr->animationCluster->getCurrentTextureSequence() != "walking_right"){
                    m_ownerEntityPtr->animationCluster->setCurrentTextureSequence("walking_right");
                }
            }
        }

        void exitScript() override{
            m_ownerEntityPtr->motionUnit->velocity.x = 0;
        }
};
class PlayerMovingLeftState : public sge::State{
    public:
        PlayerMovingLeftState(sge::Entity* playerEntity) : sge::State(playerEntity){};

        void enterScript() override{
            m_ownerEntityPtr->motionUnit->velocity.x = -100;
        }

        void updateScript(float dt) override{
            if(m_ownerEntityPtr->stateCluster->isStateActive("on_ground")){
                if(m_ownerEntityPtr->animationCluster->getCurrentTextureSequence() != "walking_left"){
                    m_ownerEntityPtr->animationCluster->setCurrentTextureSequence("walking_left");
                }
            }
        }

        void exitScript() override{
            m_ownerEntityPtr->motionUnit->velocity.x = 0;
        }
};
class PlayerJumpState : public sge::State{
    public:
        PlayerJumpState(sge::Entity* playerEntity) : sge::State(playerEntity){};

        void enterScript() override{
            // Lock double jump here if needed
            m_ownerEntityPtr->motionUnit->velocity.y = -200;
            m_ownerEntityPtr->animationCluster->setCurrentTextureSequence("in_air");
        }
};
class PlayerOnGroundState : public sge::State{
    public:
        PlayerOnGroundState(sge::Entity* playerEntity) : sge::State(playerEntity){};

        void updateScript(float dt) override{
            if(!m_ownerEntityPtr->stateCluster->isStateActive("moving_right") &&
               !m_ownerEntityPtr->stateCluster->isStateActive("moving_left")){
                    
                    m_ownerEntityPtr->animationCluster->setCurrentTextureSequence("idle");
              }
        }
};



class GravityEntity : public sge::ComplexMobileEntity{
    public :
        GravityEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups)
            : sge::ComplexMobileEntity(texture, textureRect, position, collisionGroups){
                motionUnit->fieldForces["gravity"] = sf::Vector2f(0, 1000); //.4
        }
};

class PlayerEntity : public GravityEntity{
    public:
        PlayerEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups, sge::TextureSheet* animationTextureSheet)
            : GravityEntity(texture, textureRect, position, collisionGroups){
                animationCluster = new sge::AnimationCluster(sprite);
                animationCluster->animationDelayMilliseconds = 80;
                animationCluster->addTextureSequence("idle", new sge::TextureSequence(std::vector<int>{260}, animationTextureSheet));
                animationCluster->addTextureSequence("in_air", new sge::TextureSequence(std::vector<int>{265}, animationTextureSheet));
                animationCluster->addTextureSequence("walking_right", new sge::TextureSequence(std::vector<int>{262, 263, 264}, animationTextureSheet));
                animationCluster->addTextureSequence("walking_left", new sge::TextureSequence(std::vector<int>{262, 263, 264}, animationTextureSheet, true));
                animationCluster->setCurrentTextureSequence("idle");

                collisionShapes["global_bounds"]->setSize(sf::Vector2f(16, 8));
                collisionShapes["global_bounds"]->offset = sf::Vector2f(0, 8);

                stateCluster = new sge::StateCluster();
                stateCluster->states["on_ground"] = new PlayerOnGroundState(this);
                stateCluster->states["jump"] = new PlayerJumpState(this);
                stateCluster->states["moving_right"] = new PlayerMovingRightState(this);
                stateCluster->states["moving_left"] = new PlayerMovingLeftState(this);
                stateCluster->activateState("jump"); // jump because player is initially falling
            }
};



class KeyboardController : public sge::Controller{
    public:
        KeyboardController(sge::Entity* playerEntity) : m_playerEntityPtr(playerEntity){}; 

        void script(sf::Event event) override{
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::A){
                    m_playerEntityPtr->stateCluster->deactivateState("moving_right");
                    m_playerEntityPtr->stateCluster->activateState("moving_left");
                }
                else if(event.key.code == sf::Keyboard::D){
                    m_playerEntityPtr->stateCluster->deactivateState("moving_left");
                    m_playerEntityPtr->stateCluster->activateState("moving_right");
                }

                if(event.key.code == sf::Keyboard::Space){
                    m_playerEntityPtr->stateCluster->deactivateState("on_ground");
                    m_playerEntityPtr->stateCluster->activateState("jump");
                    if(m_playerEntityPtr->stateCluster->isStateActive("jump")){
                        m_playerEntityPtr->motionUnit->velocity.y = - 200; // ! infinite jump for testing
                    }
                }
            }
            if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::A){
                    m_playerEntityPtr->stateCluster->deactivateState("moving_left");
                }
                if(event.key.code == sf::Keyboard::D){
                    m_playerEntityPtr->stateCluster->deactivateState("moving_right");
                }
            }
        }

    private:
        sge::Entity* m_playerEntityPtr;
};


int main(){
    printf(".▄▄ ·  ▄▄ • ▄▄▄ .\n▐█ ▀. ▐█ ▀ ▪▀▄.▀·\n▄▀▀▀█▄▄█ ▀█▄▐▀▀▪▄\n▐█▄▪▐█▐█▄▪▐█▐█▄▄▌\n ▀▀▀▀ ·▀▀▀▀  ▀▀▀ \n");



    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    window->setKeyRepeatEnabled(false); // For proper keyboard events handling (e.g. jumping)
    sf::View v = window->getDefaultView();
    sf::View* debugScreenView = &v;

    sge::Universe* universe = new sge::Universe(window);
    universe->setupDebugEntityManager();



    // Load assets
    universe->assetsManager->loadTextureSheet(std::filesystem::current_path().string() + "/examples/dev/assets/tilemap.png", "tileset", sge::TextureSheetSizes{16, 16, 20, 20});
    universe->assetsManager->loadFont(std::filesystem::current_path().string() + "/examples/dev/assets/m5x7.ttf", "m5x7");
    //



    universe->setupDebugScreenManager(debugScreenView, universe->assetsManager->getFont("m5x7"), 30);



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
    
    universe->debugScreenManager->addDebugVariable(
        sf::Vector2f(30, 20),
        new sge::DebugVariable{
            [playerEntity](){
                std::string activeStates = "";
                for(std::string stateName : playerEntity->stateCluster->getActiveStateNames()){
                    activeStates += " " + stateName;
                }

                return "active_states: " + activeStates;
            }
        }
    );
    universe->debugScreenManager->addDebugVariable(
        sf::Vector2f(30, 60),
        new sge::DebugVariable{
            [playerEntity](){
                return
                    "pos_x: " + std::to_string(playerEntity->sprite->getPosition().x) +
                    "   pos_y: " + std::to_string(playerEntity->sprite->getPosition().y);
            }
        }
    );
    universe->debugScreenManager->addDebugVariable(
        sf::Vector2f(30, 100),
        new sge::DebugVariable{
            [playerEntity](){
                std::string appliedForces = "";
                for(auto& [forceName, forceValue] : playerEntity->motionUnit->contactForces){
                    appliedForces += " " + forceName + " -> (" + std::to_string(forceValue.x) + ", " + std::to_string(forceValue.y) + ")";
                }
                for(auto& [forceName, forceValue] : playerEntity->motionUnit->fieldForces){
                    appliedForces += " " + forceName + " -> (" + std::to_string(forceValue.x) + ", " + std::to_string(forceValue.y) + ")";
                }
                
                return "forces: " + appliedForces;
            }
        }
    );
    universe->debugScreenManager->addDebugVariable(
        sf::Vector2f(30, 140),
        new sge::DebugVariable{
            [playerEntity](){
                return
                    "vel: (" + std::to_string(playerEntity->motionUnit->velocity.x) + ", " + std::to_string(playerEntity->motionUnit->velocity.y) + ")";
            }
        }
    );
    universe->debugScreenManager->addDebugVariable(
        sf::Vector2f(30, 180),
        new sge::DebugVariable{
            [playerEntity](){
                return
                    "acc: (" + std::to_string(playerEntity->motionUnit->acceleration.x) + ", " + std::to_string(playerEntity->motionUnit->acceleration.y) + ")";
            }
        }
    );
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

    boxEntity->motionUnit->addComputationScript("friction_force_computation", [](sge::MotionUnit* thisMotionUnit, float dt){
        if(thisMotionUnit->contactForces.count("kinetic_friction")){
            thisMotionUnit->velocity.x = sge::approach(0, abs(thisMotionUnit->contactForces["kinetic_friction"].x*dt), thisMotionUnit->velocity.x);
            thisMotionUnit->velocity.y = sge::approach(0, abs(thisMotionUnit->contactForces["kinetic_friction"].y*dt), thisMotionUnit->velocity.y);
        }
    });

    sge::DebugEntity* boxDE = new sge::DebugEntity(boxEntity);
    boxDE->customCollisionShapeBorderSettings["global_bounds"] = sge::CollisionShapeBorderSettings{sf::Color::Green};

    universe->debugScreenManager->addDebugVariable(
        sf::Vector2f(500, 20),
        new sge::DebugVariable{
            [boxEntity](){
                std::string appliedForces = "";
                for(auto& [forceName, forceValue] : boxEntity->motionUnit->contactForces){
                    appliedForces += " " + forceName + " -> (" + std::to_string(forceValue.x) + ", " + std::to_string(forceValue.y) + ")";
                }
                for(auto& [forceName, forceValue] : boxEntity->motionUnit->fieldForces){
                    appliedForces += " " + forceName + " -> (" + std::to_string(forceValue.x) + ", " + std::to_string(forceValue.y) + ")";
                }
                
                return "[box] forces: " + appliedForces;
            }
        }
    );
    universe->debugScreenManager->addDebugVariable(
        sf::Vector2f(500, 60),
        new sge::DebugVariable{
            [boxEntity](){
                return
                    "[box] vel: (" + std::to_string(boxEntity->motionUnit->velocity.x) + ", " + std::to_string(boxEntity->motionUnit->velocity.y) + ")";
            }
        }
    );
    universe->debugScreenManager->addDebugVariable(
        sf::Vector2f(500, 100),
        new sge::DebugVariable{
            [boxEntity](){
                return
                    "[box] acc: (" + std::to_string(boxEntity->motionUnit->acceleration.x) + ", " + std::to_string(boxEntity->motionUnit->acceleration.y) + ")";
            }
        }
    );
    //
    


    CameraView* cameraView = new CameraView(playerEntity);



    universe->scriptedViewManager->registerComponent(cameraView);

    universe->entityManager->registerComponent(cameraView, playerEntity);
    universe->debugEntityManager->registerComponent(cameraView, playerDE);

    universe->entityManager->registerComponent(cameraView, boxEntity);
    universe->debugEntityManager->registerComponent(cameraView, boxDE);

    for(sge::Entity* entity : mapTileEntities){
        universe->entityManager->registerComponent(cameraView, entity);
    }



    // * Notes:
    // ! The collision shape CAN NOT be the initiator AND the recepient of the AABB response
    // ! To work properly, all AABB recipients with common initiator should be put together
    universe->collisionManager->registerComponent(new AABBInteraction({"player"}, {"tiles", "box"}));
    universe->collisionManager->registerComponent(new PlayerSurfaceInteraction({"player"}, {"tiles", "box"}));
    universe->collisionManager->registerComponent(new AABBInteraction({"box"}, {"tiles"}));
    universe->collisionManager->registerComponent(new BoxSurfaceInteraction({"box"}, {"tiles"}));
    universe->collisionManager->registerComponent(new PushInteraction({"player"}, {"box"}, boxDE));



    universe->controllerManager->registerComponent(new KeyboardController(playerEntity));



    universe->loop();

    return 0;
}