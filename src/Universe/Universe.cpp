#include "Universe.h"

Universe::Universe(PhysicsManager* t_physicsManager, CollisionManager* t_collisionManager, TextureManager* t_textureManager, EntityManager* t_entityManager){
    physicsManager = t_physicsManager;
    collisionManager = t_collisionManager;
    textureManager = t_textureManager;
    entityManager = t_entityManager;
}

Universe::Universe(PhysicsManager* t_physicsManager, CollisionManager* t_collisionManager, TextureManager* t_textureManager, EntityManager* t_entityManager, DebugManager* t_debugManager){
    physicsManager = t_physicsManager;
    collisionManager = t_collisionManager;
    textureManager = t_textureManager;
    entityManager = t_entityManager;
    debugManager = t_debugManager;
}


void Universe::setupWindow(sf::RenderWindow *window){ m_windowPtr = window; }




void Universe::addController(std::function<void()> controller){ m_controllers.push_back(controller); }
void Universe::addEventHandler(std::function<void(sf::Event event)> eventHandler){ m_eventHandlers.push_back(eventHandler); }



void Universe::loop(){
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
        
        for(PhysicalObject* physicalObject : physicsManager->getAllPhysicalObjects()){
            m_windowPtr->draw(*physicalObject);
        }

        if(debugManager){
            debugManager->showDebugInfo(m_windowPtr);
        }
        //

        m_windowPtr->display();
    }
}