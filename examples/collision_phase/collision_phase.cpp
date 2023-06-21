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


class CollisionHighlightInteraction : public sge::CollisionInteraction{
    public:
        CollisionHighlightInteraction(
            std::vector<std::string> initiatorGroups,
            std::vector<std::string> recipientGroups,
            std::vector<sge::DebugEntity*> mapTileDebugEntities)
                : sge::CollisionInteraction(initiatorGroups, recipientGroups),
                  m_mapTileDebugEntities(mapTileDebugEntities){};


        bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{ return sge::boundingBox(initiator, recipient); }


        void startPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            for(sge::Collision collision : collisions){
                for(sge::DebugEntity* surfaceDebugEntitity : m_mapTileDebugEntities){
                    if(surfaceDebugEntitity->getRelatedEntity() == collision.recipient->getOwnerEntity()){
                        surfaceDebugEntitity->customCollisionShapeBorderSettings["global_bounds"] = sge::CollisionShapeBorderSettings{sf::Color::Red};
                    }
                }
            }
        }

        void endPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
            for(sge::Collision collision : collisions){
                for(sge::DebugEntity* surfaceDebugEntitity : m_mapTileDebugEntities){
                    if(surfaceDebugEntitity->getRelatedEntity() == collision.recipient->getOwnerEntity()){
                        surfaceDebugEntitity->customCollisionShapeBorderSettings["global_bounds"] = sge::CollisionShapeBorderSettings();
                    }
                }
            }
        }

    private:
        std::vector<sge::DebugEntity*> m_mapTileDebugEntities;
};



int main(){
    printf(".▄▄ ·  ▄▄ • ▄▄▄ .\n▐█ ▀. ▐█ ▀ ▪▀▄.▀·\n▄▀▀▀█▄▄█ ▀█▄▐▀▀▪▄\n▐█▄▪▐█▐█▄▪▐█▐█▄▄▌\n ▀▀▀▀ ·▀▀▀▀  ▀▀▀ \n");



    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Collision Phase");
    window->setKeyRepeatEnabled(false); // For proper keyboard events handling (e.g. jumping)
    
    sge::Universe* universe = new sge::Universe(window);
    universe->setupDebugEntityManager();



    // Load assets
    universe->assetsManager->loadTextureSheet(
        std::filesystem::current_path().string() + "/examples/collision_phase/assets/tilemap.png",
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

    sge::DebugEntity* playerDE = new sge::DebugEntity(playerEntity);
    playerDE->customCollisionShapeBorderSettings["global_bounds"] = sge::CollisionShapeBorderSettings{sf::Color::Red};
    //



    // Map
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
    
    std::vector<sge::DebugEntity*> mapTileDebugEntities;
    for(sge::Entity* surfaceEntity : mapTileEntities){
        mapTileDebugEntities.push_back(new sge::DebugEntity(surfaceEntity));
    }
    //



    CameraView* cameraView = new CameraView(playerEntity);



    universe->scriptedViewManager->registerComponent(cameraView);

    universe->entityManager->registerComponent(cameraView, playerEntity);
    universe->debugEntityManager->registerComponent(cameraView, playerDE);

    for(sge::Entity* tileEntity : mapTileEntities){
        universe->entityManager->registerComponent(cameraView, tileEntity);
    }
    for(sge::DebugEntity* tileDebugEntity : mapTileDebugEntities){
        universe->debugEntityManager->registerComponent(cameraView, tileDebugEntity);
    }



    universe->collisionManager->registerComponent(new AABBInteraction({"player"}, {"tiles"}));
    universe->collisionManager->registerComponent(new PlayerSurfaceInteraction({"player"}, {"tiles"}));
    universe->collisionManager->registerComponent(new CollisionHighlightInteraction({"player"}, {"tiles"}, mapTileDebugEntities));



    universe->controllerManager->registerComponent(new KeyboardController(playerEntity));

    


    universe->loop();
    return 0;
}