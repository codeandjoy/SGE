#include <filesystem>
#include <iostream>
#include <vector>

#include "../../SGE.hpp"

#include "../_common/PlayerStates.h"
#include "../_common/AABBInteraction.h"
#include "../_common/PlayerSurfaceInteraction.h"
#include "../_common/CameraView.h"
#include "../_common/CustomEntities.h"
#include "../_common/KeyboardController.h"

#include "SetupLevel1Scene.h"
#include "SetupLevel2Scene.h"


class PlayerCoinInteraction : public sge::CollisionInteraction{
    public:
        PlayerCoinInteraction(std::vector<std::string> initiatorGroups, std::vector<std::string> recipientGroups, sge::Universe* universe)
            : universePtr(universe), sge::CollisionInteraction(initiatorGroups, recipientGroups){}

        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }

        void startPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            // Reset player's position
            collisions[0].initiator->getOwnerEntity()->sprite->setPosition(sf::Vector2f(200, 100));

            universePtr->drumSceneManager->setCurrentScene("level2");
        }
    
    private:
        sge::Universe* universePtr;
};

class PlayerHeartInteraction : public sge::CollisionInteraction{
    public:
        PlayerHeartInteraction(std::vector<std::string> initiatorGroups, std::vector<std::string> recipientGroups, sge::Universe* universe)
            : universePtr(universe), sge::CollisionInteraction(initiatorGroups, recipientGroups){}

        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }

        void startPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            // Reset player's position
            collisions[0].initiator->getOwnerEntity()->sprite->setPosition(sf::Vector2f(200, 100));

            universePtr->drumSceneManager->setCurrentScene("level1");
        }
    
    private:
        sge::Universe* universePtr;
};


int main(){
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Test");
    window->setKeyRepeatEnabled(false); // For proper keyboard events handling (e.g. jumping)

    sge::Universe* universe = new sge::Universe(window);



    // Load assets
    universe->assetsManager->loadTextureSheet(
        std::filesystem::current_path().string() + "/examples/dev/assets/tilemap.png",
        "tileset",
        sge::TextureSheetSizes{16, 16, 20, 20}
    );
    //



    // Player
    PlayerEntity* playerEntity = new PlayerEntity(
        universe->assetsManager->getTextureSheet("tileset")->getTexture(),
        universe->assetsManager->getTextureSheet("tileset")->getTextureRect(260),
        sf::Vector2f(200, 100),
        {"player"},
        universe->assetsManager->getTextureSheet("tileset")
    );
    //



    CameraView* cameraView = new CameraView(playerEntity);



    sge::Scene* level1 = setupLevel1Scene(universe, cameraView);
    sge::Scene* level2 = setupLevel2Scene(universe, cameraView);



    universe->scriptedViewManager->registerComponent(cameraView);
    universe->entityManager->registerComponent(cameraView, playerEntity);
    universe->drumSceneManager->registerComponent("level1", level1);
    universe->drumSceneManager->registerComponent("level2", level2);
    universe->drumSceneManager->setCurrentScene("level1");



    universe->collisionManager->registerComponent(new AABBInteraction({"player"}, {"tiles"}));
    universe->collisionManager->registerComponent(new PlayerSurfaceInteraction({"player"}, {"tiles"}));
    universe->collisionManager->registerComponent(new PlayerCoinInteraction({"player"}, {"coin"}, universe));
    universe->collisionManager->registerComponent(new PlayerHeartInteraction({"player"}, {"heart"}, universe));



    universe->controllerManager->registerComponent(new KeyboardController(playerEntity));



    universe->loop();

    return 0;
}