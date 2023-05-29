#include "Universe.h"
#include "../Assets/AssetsManager/AssetsManager.h"
#include "../Controller/ControllerManager.h"
#include "../Debug/DebugManager/DebugManager.h"
#include "../View/ScriptedViewManager.h"

#include "../Logic/Sprite/SpriteManager.h"
#include "../Logic/Physics/PhysicsManager.h"
#include "../Logic/CollisionShape/CollisionShapeManager.h"
#include "../Logic/ClickableShape/ClickableShapeManager.h"
#include "../Logic/SpriteText/SpriteTextManager.h"
#include "../Logic/Animation/AnimationManager.h"
#include "../Logic/Collision/CollisionManager.h"
#include "../Logic/Entity/EntityManager.h"
#include "../Logic/Scene/SceneManager.h"


sge::Universe::Universe(){
    sge::AssetsManager* AsM = new sge::AssetsManager();
    sge::ControllerManager* CoM = new sge::ControllerManager();

    sge::ScriptedViewManager* VM = new sge::ScriptedViewManager();
    sge::SpriteManager* SpM = new sge::SpriteManager();
    sge::PhysicsManager* PM = new sge::PhysicsManager();
    sge::CollisionShapeManager* CSM = new sge::CollisionShapeManager();
    sge::ClickableShapeManager* ClSM = new sge::ClickableShapeManager();
    sge::SpriteTextManager* STM = new SpriteTextManager();
    sge::AnimationManager* AnM = new sge::AnimationManager();
    sge::CollisionManager* CM = new sge::CollisionManager();
    sge::EntityManager* EM = new sge::EntityManager(SpM, PM, CSM, AnM, CM);
    sge::SceneManager* ScM = new sge::SceneManager(SpM, PM, CSM, AnM, CM, EM);

    assetsManager = AsM;
    controllerManager = CoM;
    scriptedViewManager = VM;

    m_spriteManager = SpM;
    m_physicsManager = PM;
    m_collisionShapeManager = CSM;
    m_clickableShapeManager = ClSM;
    m_spriteTextManager = STM;
    m_animationManager = AnM;
    collisionManager = CM;
    entityManager = EM;
    sceneManager = ScM;
}



void sge::Universe::setupWindow(sf::RenderWindow *window){
    m_windowPtr = window;
    m_uiView = window->getDefaultView();
}
void sge::Universe::setupDebug(){
    sge::DebugManager* debugManagerPtr = new sge::DebugManager();
    debugManager = debugManagerPtr;

   sceneManager->setupDebug(debugManagerPtr);
}


void sge::Universe::loop(){
    if(!m_windowPtr){
        printf("RenderWindow is not initialized. Use setupWindow method to initialize RenderWindow before(!) looping the Universe.\n");
        exit(1);
    }

    m_deltaClock.restart();

    while(m_windowPtr->isOpen()){
        sf::Time deltaTime = m_deltaClock.restart();
        float dt = deltaTime.asSeconds();
        if(dt > 0.15f) dt = 0.15f;


        sf::Event event;
        while(m_windowPtr->pollEvent(event)){
            if(event.type == sf::Event::Closed) m_windowPtr->close();
            if(event.type == sf::Event::Resized){
                m_uiView.setSize({
                    static_cast<float>(event.size.width),
                    static_cast<float>(event.size.height)
                });
            }

            controllerManager->updateControllers(event);
            m_clickableShapeManager->updateClickableShapes(event);
        }


        if(!isPaused){
            m_physicsManager->updatePhysics(dt);
            m_collisionShapeManager->alignCollisionShapes();
            collisionManager->updateCollisions();
            m_animationManager->updateAnimations();
            scriptedViewManager->runViewScripts();
            sceneManager->alignScene(); // Scene can be reset only after all managers finished their updates to prevent segfaults
        }
        m_clickableShapeManager->alignClickableShapes();
        m_spriteTextManager->alignSpriteTextObjects();
        
        m_windowPtr->clear();
        
        m_spriteManager->drawSprites(m_windowPtr);
        debugManager->showDebugInfo(m_windowPtr); // ? show in ui view
       
        m_windowPtr->setView(m_uiView);
        m_spriteTextManager->drawSpriteTextObjects(m_windowPtr);

        m_windowPtr->display();
    }
}