#include "Universe.h"
#include "../AssetsManager/AssetsManager.h"
#include "../SpriteManager/SpriteManager.h"
#include "../Physics/PhysicsManager.h"
#include "../Physics/PhysicalObject.h"
#include "../Collision/CollisionManager.h"
#include "../Animation/AnimationManager.h"
#include "../Entity/EntityManager.h"
#include "../Debug/DebugManager.h"
#include "../Scene/SceneManager.h"
#include "../UI/UISpriteManager/UISpriteManager.h"
#include "../UI/ClickableShape/ClickableShape.h"
#include "../UI/ClickableShape/ClickableShapeManager.h"
#include "../UI/SpriteText/SpriteText.h"
#include "../UI/SpriteText/SpriteTextManager.h"
#include "../UI/UIAnimationManager/UIAnimationManager.h"
#include "../UI/UIEntity/UIEntityManager.h"

sge::Universe::Universe(){
    sge::AssetsManager* AsM = new sge::AssetsManager();
    sge::SpriteManager* SpM = new sge::SpriteManager();
    sge::PhysicsManager* PM = new sge::PhysicsManager();
    sge::CollisionManager* CM = new sge::CollisionManager();
    sge::AnimationManager* AnM = new sge::AnimationManager();
    sge::EntityManager* EM = new sge::EntityManager(SpM, PM, CM, AnM);
    sge::DebugManager* DM = new sge::DebugManager();
    sge::SceneManager* ScM = new sge::SceneManager(PM, CM, AnM, EM, DM);

    assetsManager = AsM;
    spriteManager = SpM;
    physicsManager = PM;
    collisionManager = CM;
    animationManager = AnM;
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



void sge::Universe::addController(std::function<void()> controller){ m_controllers.push_back(controller); }
void sge::Universe::addEventHandler(std::function<void(sf::Event event)> eventHandler){ m_eventHandlers.push_back(eventHandler); }



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
        // Events
        sf::Event event;
        while(m_windowPtr->pollEvent(event)){
            if (event.type == sf::Event::Closed) m_windowPtr->close();
        
            for(std::function eventHandler : m_eventHandlers){
                eventHandler(event);
            }

            // UI events
            for(ClickableShape* clickableShape : clickableShapeManager->getAllActiveClickableShapes()){
                clickableShape->action(clickableShape, event);
            }
            //
        }
        //

        // Controllers
        for(std::function controller : m_controllers){
            controller();
        }
        //

        // Game updates
        // Calculate dt
        sf::Time deltaTime = m_deltaClock.restart();
        float dt = deltaTime.asSeconds();
        if(dt > 0.15f) dt = 0.15f;
        //
        
        if(!isPaused){
            physicsManager->updatePhysics(dt);
            collisionManager->alignCollisionShapes();
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