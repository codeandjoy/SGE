#include "Universe.h"
#include "../Assets/AssetsManager/AssetsManager.h"
#include "../Controller/ControllerManager.h"
#include "../Debug/DebugManager.h"
#include "../Debug/DebugScreen/DebugScreenManager.h"
#include "../View/ScriptedViewManager.h"

#include "../Logic/Sprite/SpriteManager.h"
#include "../Logic/Physics/PhysicsManager.h"
#include "../Logic/CollisionShape/CollisionShapeManager.h"
#include "../Logic/ClickableShape/ClickableShapeManager.h"
#include "../Logic/SpriteText/SpriteTextManager.h"
#include "../Logic/Animation/AnimationManager.h"
#include "../Logic/State/StateManager.h"
#include "../Logic/Collision/CollisionManager.h"
#include "../Logic/Entity/EntityManager.h"
#include "../Logic/Scene/DrumSceneManager.h"
#include "../Logic/Scene/LayerSceneManager.h"


sge::Universe::Universe(sf::RenderWindow* window){
    m_windowPtr = window;
    
    sge::AssetsManager* AsM = new sge::AssetsManager();
    sge::ControllerManager* CoM = new sge::ControllerManager();

    sge::ScriptedViewManager* VM = new sge::ScriptedViewManager();
    sge::SpriteManager* SpM = new sge::SpriteManager();
    sge::PhysicsManager* PM = new sge::PhysicsManager();
    sge::CollisionShapeManager* CSM = new sge::CollisionShapeManager();
    sge::ClickableShapeManager* ClSM = new sge::ClickableShapeManager();
    sge::SpriteTextManager* STM = new SpriteTextManager();
    sge::AnimationManager* AnM = new sge::AnimationManager();
    sge::StateManager* StM = new sge::StateManager();
    sge::CollisionManager* CM = new sge::CollisionManager(CSM);
    sge::EntityManager* EM = new sge::EntityManager(SpM, PM, CSM, ClSM, STM, AnM, StM);
    sge::DrumSceneManager* DrSM = new sge::DrumSceneManager(EM);
    sge::LayerSceneManager* LaSM = new sge::LayerSceneManager(EM);

    assetsManager = AsM;
    controllerManager = CoM;
    scriptedViewManager = VM;

    m_spriteManager = SpM;
    m_physicsManager = PM;
    m_collisionShapeManager = CSM;
    m_clickableShapeManager = ClSM;
    m_spriteTextManager = STM;
    m_animationManager = AnM;
    m_stateManager = StM;
    collisionManager = CM;
    entityManager = EM;
    drumSceneManager = DrSM;
    layerSceneManager = LaSM;
}



void sge::Universe::setupDebugEntityManager(){
    sge::DebugManager* debugManagerPtr = new sge::DebugManager();
    debugManager = debugManagerPtr;

   drumSceneManager->setupDebug(debugManagerPtr);
   layerSceneManager->setupDebug(debugManagerPtr);
}
void sge::Universe::setupDebugScreenManager(sf::View* debugScreenView, sf::Font* debugScreenFont, int fontSize = 20){
    debugScreenManager = new sge::DebugScreenManager(entityManager, debugScreenView, debugScreenFont, fontSize);
}


void sge::Universe::loop(){
    m_deltaClock.restart();

    while(m_windowPtr->isOpen()){
        // dt
        sf::Time deltaTime = m_deltaClock.restart();
        float dt = deltaTime.asSeconds();
        if(dt > dtCap) dt = dtCap;
        //


        // Event
        sf::Event event;
        while(m_windowPtr->pollEvent(event)){
            if(event.type == sf::Event::Closed) m_windowPtr->close();

            controllerManager->processEvent(event);
            m_clickableShapeManager->processEvent(event);
        }
        //


        // Update
        m_physicsManager->update(dt);
        m_collisionShapeManager->update(dt);
        m_clickableShapeManager->update(dt);
        m_spriteTextManager->update(dt);
        m_stateManager->update(dt);
        collisionManager->updateCollisions();

        m_animationManager->update(dt);
        scriptedViewManager->update(dt);

        debugScreenManager->updateDebugVariables();

        drumSceneManager->alignScene(); // Scene can be reset only after all managers finished their updates to prevent segfaults in loops
        //

        
        // Draw
        m_windowPtr->clear();
        
        m_spriteManager->draw(m_windowPtr);
        m_spriteTextManager->draw(m_windowPtr);
        if(debugManager) debugManager->draw(m_windowPtr);

        m_windowPtr->display();
        //
    }
}