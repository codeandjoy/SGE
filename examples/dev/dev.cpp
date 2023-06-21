#include <stdio.h>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "../../SGE.hpp"

#include "../_common/PlayerStates.h"
#include "../_common/AABBInteraction.h"
#include "../_common/PlayerSurfaceInteraction.h"
#include "../_common/CameraView.h"
#include "../_common/CustomEntities.h"
#include "../_common/KeyboardController.h"
#include "../_common/Map.h"
#include "BoxSurfaceInteraction.h"
#include "PushInteraction.h"
#include "MapController.h"



int main(){
    printf(".▄▄ ·  ▄▄ • ▄▄▄ .\n▐█ ▀. ▐█ ▀ ▪▀▄.▀·\n▄▀▀▀█▄▄█ ▀█▄▐▀▀▪▄\n▐█▄▪▐█▐█▄▪▐█▐█▄▄▌\n ▀▀▀▀ ·▀▀▀▀  ▀▀▀ \n");



    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    window->setKeyRepeatEnabled(false); // For proper keyboard events handling (e.g. jumping)
    sf::View v = window->getDefaultView();
    sf::View* debugScreenView = &v;

    sge::Universe* universe = new sge::Universe(window);
    universe->setupDebugEntityManager();



    // Load assets
    universe->assetsManager->loadTextureSheet(
        std::filesystem::current_path().string() + "/examples/dev/assets/tilemap.png",
        "tileset",
        sge::TextureSheetSizes{16, 16, 20, 20}
    );
    universe->assetsManager->loadFont(
        std::filesystem::current_path().string() + "/examples/dev/assets/m5x7.ttf",
        "m5x7"
    );
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



    std::vector<sge::Entity*> mapTileEntities;

    for(int i = 0; i < map::tileCountY; i++){
        for(int j = 0; j < map::tileCountX; j++){
            if(map::map_data[map::tileCountX*i+j] != 0){
                mapTileEntities.push_back(new sge::StaticEntity(
                    universe->assetsManager->getTextureSheet("tileset")->getTexture(),
                    universe->assetsManager->getTextureSheet("tileset")->getTextureRect(map::map_data[map::tileCountX*i+j] - 1),
                    sf::Vector2f(j*map::tileSizeX, i*map::tileSizeY),
                    {"tiles"}
                ));
            }
        }
    }



    GravityEntity* boxEntity = new GravityEntity(
        universe->assetsManager->getTextureSheet("tileset")->getTexture(),
        universe->assetsManager->getTextureSheet("tileset")->getTextureRect(27),
        sf::Vector2f(360, 160),
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
    // ! To work properly, all AABB recipients with common initiator should be put together
    universe->collisionManager->registerComponent(new AABBInteraction({"player"}, {"tiles", "box"}));
    universe->collisionManager->registerComponent(new PlayerSurfaceInteraction({"player"}, {"tiles", "box"}));
    universe->collisionManager->registerComponent(new AABBInteraction({"box"}, {"tiles"}));
    universe->collisionManager->registerComponent(new BoxSurfaceInteraction({"box"}, {"tiles"}));
    universe->collisionManager->registerComponent(new PushInteraction({"player"}, {"box"}, boxDE));



    universe->controllerManager->registerComponent(new KeyboardController(playerEntity));
    universe->controllerManager->registerComponent(new MapController(boxEntity));



    universe->loop();

    return 0;
}