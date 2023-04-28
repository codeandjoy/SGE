#include "Universe.h"
#include "../Physics/PhysicsManager.h"
#include "../Physics/PhysicalObject.h"
#include "../Collision/CollisionManager.h"
#include "../Texture/TextureManager.h"
#include "../Entity/EntityManager.h"
#include "../Debug/DebugManager.h"
#include "../Scene/SceneManager.h"


sge::Universe::Universe(){
    sge::PhysicsManager* PM = new sge::PhysicsManager();
    sge::CollisionManager* CM = new sge::CollisionManager();
    sge::TextureManager* TM = new sge::TextureManager();
    sge::EntityManager* EM = new sge::EntityManager(PM, CM, TM);
    sge::DebugManager* DM = new sge::DebugManager();
    sge::SceneManager* SM = new sge::SceneManager(PM, CM, TM, EM, DM);

    physicsManager = PM;
    collisionManager = CM;
    textureManager = TM;
    entityManager = EM;
    debugManager = DM;
    sceneManager = SM;
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
    textureManager->initAnimationClocks();
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

        physicsManager->updatePhysics(dt);
        collisionManager->alignCollisionShapes();
        collisionManager->updateCollisions();
        textureManager->updateAnimations();
        // 

        // Game draws
        m_windowPtr->clear();
        
        for(sge::PhysicalObject* physicalObject : physicsManager->getAllPhysicalObjects()){
            m_windowPtr->draw(*physicalObject);
        }

        debugManager->showDebugInfo(m_windowPtr);
        //

        m_windowPtr->display();
    }
}