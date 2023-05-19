#include "Universe.h"
#include "../Assets/AssetsManager/AssetsManager.h"
#include "../Controller/ControllerManager.h"
#include "../Common/ClickableShape/ClickableShape.h"
#include "../Common/ClickableShape/ClickableShapeManager.h"
#include "../Logic/SpriteManager/SpriteManager.h"
#include "../Logic/Physics/PhysicsManager.h"
#include "../Logic/Physics/PhysicalObject.h"
#include "../Logic/CollisionShape/CollisionShapeManager.h"
#include "../Logic/AnimationManager/AnimationManager.h"
#include "../Logic/Collision/CollisionManager.h"
#include "../Logic/Entity/EntityManager.h"
#include "../Logic/Debug/DebugManager.h"
#include "../Logic/Scene/SceneManager.h"
#include "../UI/UISpriteManager/UISpriteManager.h"
#include "../UI/SpriteText/SpriteText.h"
#include "../UI/SpriteText/SpriteTextManager.h"
#include "../UI/UIAnimationManager/UIAnimationManager.h"
#include "../UI/UIEntity/UIEntityManager.h"


sge::Universe::Universe(){
    sge::AssetsManager* AsM = new sge::AssetsManager();
    sge::ControllerManager* CoM = new sge::ControllerManager();

    sge::SpriteManager* SpM = new sge::SpriteManager();
    sge::PhysicsManager* PM = new sge::PhysicsManager();
    sge::CollisionShapeManager* CSM = new sge::CollisionShapeManager();
    sge::AnimationManager* AnM = new sge::AnimationManager();
    sge::CollisionManager* CM = new sge::CollisionManager();
    sge::EntityManager* EM = new sge::EntityManager(SpM, PM, CSM, AnM, CM);
    sge::DebugManager* DM = new sge::DebugManager();
    sge::SceneManager* ScM = new sge::SceneManager(SpM, PM, CSM, AnM, CM, EM, DM);

    assetsManager = AsM;
    controllerManager = CoM;
    spriteManager = SpM;
    physicsManager = PM;
    collisionShapeManager = CSM;
    animationManager = AnM;
    collisionManager = CM;
    entityManager = EM;
    debugManager = DM;
    sceneManager = ScM;
    
    sge::UISpriteManager* UISM = new sge::UISpriteManager();
    sge::ClickableShapeManager* UICSM = new sge::ClickableShapeManager();
    sge::SpriteTextManager* UISTM = new SpriteTextManager();
    sge::UIAnimationManager* UIAM = new UIAnimationManager();
    sge::UIEntityManager* UIEM = new UIEntityManager(UISM, UICSM, UISTM, UIAM);

    uiSpriteManager = UISM;
    clickableShapeManager = UICSM;
    spriteTextManager = UISTM;
    uiAnimationManager = UIAM;
    uiEntityManager = UIEM;
}



void sge::Universe::setupWindow(sf::RenderWindow *window){ m_windowPtr = window; }



void sge::Universe::loop(){
    if(!m_windowPtr){
        printf("RenderWindow is not initialized. Use setupWindow method to initialize RenderWindow before(!) looping the Universe.\n");
        exit(1);
    }

    // Clocks initialization
    // ! Remove in the future (init on animation creation?)
    animationManager->initAnimationClocks();
    // !

    m_deltaClock.restart();
    //

    while(m_windowPtr->isOpen()){
        // Calculate dt
        sf::Time deltaTime = m_deltaClock.restart();
        float dt = deltaTime.asSeconds();
        if(dt > 0.15f) dt = 0.15f;
        //


        // Events
        sf::Event event;
        while(m_windowPtr->pollEvent(event)){
            if (event.type == sf::Event::Closed) m_windowPtr->close();
        
            for(std::function controller : controllerManager->getAllControllers()){
                controller(event);
            }

            // UI events
            for(ClickableShape* clickableShape : clickableShapeManager->getAllActiveClickableShapes()){
                clickableShape->action(clickableShape, event);
            }
            //
        }
        //


        // Game updates
        if(!isPaused){
            physicsManager->updatePhysics(dt);
            collisionShapeManager->alignCollisionShapes();
            collisionManager->updateCollisions();
            animationManager->updateAnimations();
            sceneManager->alignScene(); // Scene can be reset only after all managers finished their updates to prevent segfaults
        }

        clickableShapeManager->alignClickableShapes();
        spriteTextManager->alignSpriteTextObjects();
        uiAnimationManager->updateActiveAnimations();
        //

        
        // Game draws
        m_windowPtr->clear();
        
        for(sf::Sprite* sprite : spriteManager->getSprites()){
            m_windowPtr->draw(*sprite);
        }
        debugManager->showDebugInfo(m_windowPtr);

        for(sf::Sprite* sprite : uiSpriteManager->getAllVisibleSprites()){
            m_windowPtr->draw(*sprite);
        }
        for(sge::SpriteText* spriteText : spriteTextManager->getAllVisibleSpriteTextObjects()){
            m_windowPtr->draw(*spriteText);
        }
        //

        m_windowPtr->display();
    }
}