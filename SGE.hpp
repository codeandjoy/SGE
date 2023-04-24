#ifndef SGE_HPP
#define SGE_HPP

#include <SFML/Graphics.hpp>

#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

namespace sge{
    class PhysicsManager;
    class PhysicalObject;
    class CollisionManager;
    class TextureManager;
    class EntityManager;
    class DebugManager;
    
    class Universe{
        public:
            Universe(bool DEBUG = false);

            void setupWindow(sf::RenderWindow* window);

            void addController(std::function<void()> controller);
            void addEventHandler(std::function<void(sf::Event event)> eventHandler);

            void loop();

            sge::PhysicsManager* physicsManager = nullptr;
            sge::CollisionManager* collisionManager = nullptr;
            sge::TextureManager* textureManager = nullptr;
            sge::EntityManager* entityManager = nullptr;
            sge::DebugManager* debugManager = nullptr;

        private:
            sf::RenderWindow* m_windowPtr;

            sf::Clock m_deltaClock;
            
            std::vector<std::function<void()>> m_controllers;
            std::vector<std::function<void(sf::Event event)>> m_eventHandlers;
    };
}

#endif

#ifndef TEXTURESHEET_H
#define TEXTURESHEET_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#ifndef TEXTURE_SHEET_SIZES_H
#define TEXTURE_SHEET_SIZES_H

namespace sge{
    struct TextureSheetSizes{
        int textureSizeX;
        int textureSizeY;
        int numTexturesX;
        int numTexturesY;
    };
}

#endif

namespace sge{
    // TODO texturesheet with gaps between textures
    class TextureSheet{
        public:
            TextureSheet(sge::TextureSheetSizes textureSheetSizes, std::string location);

            std::string getLocation();
            sf::Texture* getTextureSheet();
            sf::IntRect getTextureRect(int textureN);

        private:
            std::string m_location;
            sf::Texture m_textureSheet;
            std::vector<sf::IntRect> m_textureRects;
    };
}

#endif

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>

namespace sge{
    class TextureSheet;
    class Animation;

    class TextureManager{
        public:
            void loadTexture(std::string location, std::string name, sge::TextureSheetSizes textureSheetSizes);
            sge::TextureSheet* getTexture(std::string name);

            void registerAnimation(sge::Animation* animation);
            void deregisterAnimation(sge::Animation* animation);

            void initAnimationClocks();
            void updateAnimations();

        private:
            std::unordered_map<std::string, sge::TextureSheet*> m_loadedTextures;
            std::vector<sge::Animation*> m_animations;
    };
}

#endif
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace sge{
    class TextureSheet;

    // TODO Animations should switch immediately
    class Animation{
        public:
            Animation(sge::TextureSheet* textureSheet, sf::Sprite* owner, int initialTextureN);
        
            
            void addTextureSequence(std::string name, std::vector<int> textureSequence);
            void setCurrentTextureSequence(std::string name);
        

            // ?
            // runForward -> 1,2,3,1,2,3
            // runCycle -> 1,2,3,2,1,2
            // ?
            void run();
            void restartClock();

        private:
            sf::Sprite* m_owner;
            sge::TextureSheet* m_textureSheet;
            
            sf::Clock m_clock;
            std::unordered_map<std::string, std::vector<int>> m_textureSequences; // e.g. "idle": [5, 6, 7, 8]
            std::string m_currentTextureSequence;
            int m_currentTextureN = 0;

    };
}

#endif

#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include <vector>

namespace sge{
    class PhysicalObject;

    class PhysicsManager{
        public:
            void registerPhysicalObject(sge::PhysicalObject* physicalObject);
            void deregisterPhysicalObject(sge::PhysicalObject* physicalObject);
            std::vector<sge::PhysicalObject*> getAllPhysicalObjects();

            void updatePhysics(float dt);

        private:
            std::vector<sge::PhysicalObject*> m_physicalObjects;
    };
}

#endif
#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

namespace sge{
    class PhysicalObject : public sf::Sprite{
        public:
            sf::Vector2f velocity = sf::Vector2f(0, 0);
            sf::Vector2f acceleration = sf::Vector2f(0, 0);

            void createAction(std::string name, std::function<void()> action);
            void doAction(std::string name);

            void createContinuousComputation(std::string name, std::function<void(sge::PhysicalObject*, float)> computation);

            void createFlag(std::string name);
            bool getFlag(std::string flagName);
            void setFlag(std::string flagName, bool value);        

            void update(float dt);

        private:
            std::unordered_map<std::string, std::function<void()>> m_actions;
            std::unordered_map<std::string, std::function<void(sge::PhysicalObject*, float)>> m_continuousComputations;
            std::vector<std::string> m_continuousComputationOrder;
            std::unordered_map<std::string, bool> m_flags;
    };
}

#endif
#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include <SFML/Graphics.hpp>
#include <functional>

namespace sge{
    class PhysicalObject;

    std::function<void(sge::PhysicalObject*, float)> updatePositionBasedOnVelocity();

    std::function<void(sge::PhysicalObject*, float)> updateVelocityBasedOnAcceleration(sf::Vector2f speedLimit=sf::Vector2f(9999, 9999));
}

#endif

#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

namespace sge{
    struct Collision;
    struct CollisionPair;
    class CollisionShape;

    class CollisionManager{
        public:
            void registerCollisionShape(sge::CollisionShape* collisionShape);
            void deregisterCollisionShape(sge::CollisionShape* collisionShape);
            void registerCollisionShapes(std::vector<sge::CollisionShape*> collisionShapes);
            void degisterCollisionShapes(std::vector<sge::CollisionShape*> collisionShapes);
            std::vector<sge::CollisionShape*> getAllCollisionShapes();
            void alignCollisionShapes();

            void registerCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionGroup);
            void deregisterCollisionGroup(std::string name);
            void registerCollisionGroups(std::unordered_map<std::string, std::vector<sge::CollisionShape*>> collisionGroups);
            void deregisterCollisionGroups(std::unordered_map<std::string, std::vector<sge::CollisionShape*>> collisionGroups);
            std::unordered_map<std::string, std::vector<sge::CollisionShape*>> getCollisionGroups();

            void createCollisionPair(std::string name, std::string initiatorGroup, std::string recipientGroup);
            void setPairCollisionDetectionAlgorithm(std::string collisionPairName, std::function<bool(sge::CollisionShape*, sge::CollisionShape*)> collisionDetectionAlgorithm);
            void setPairCollisionResponse(std::string collisionPairName, std::string collisionPhase, std::function<void(std::vector<sge::Collision>)> response);

            void updateCollisions();

        private:
            std::vector<sge::CollisionShape*> m_allCollisionShapes;
            std::unordered_map<std::string, std::vector<sge::CollisionShape*>> m_collisionGroups;
            std::unordered_map<std::string, sge::CollisionPair*> m_collisionPairs;
            std::vector<std::string> m_collisionPairsOrder;
    };
}

#endif
#ifndef COLLISION_PAIR_H
#define COLLISION_PAIR_H

#include <functional>
#include <unordered_map>
#include <vector>
#include <utility>
#include <string>

namespace sge{
    struct Collision;
    class CollisionShape;

    struct CollisionPair{
        std::pair<std::string, std::string> collisionGroups;
        
        std::function<void(std::vector<sge::Collision>)> startPhaseCollisionResponse;
        std::function<void(std::vector<sge::Collision>)> continuousPhaseCollisionResponse;
        std::function<void(std::vector<sge::Collision>)> endPhaseCollisionResponse;

        std::unordered_map<sge::CollisionShape*, std::vector<sge::Collision>> pastCollisions;
        
        std::function<bool(sge::CollisionShape *initiator, sge::CollisionShape *recipient)> checkCollision;
    };
}

#endif
#ifndef COLLISION_SIDE_H
#define COLLISION_SIDE_H

namespace sge{
    enum CollisionSide : int{ left, right, top, bottom };
}

#endif
#ifndef COLLISION_H
#define COLLISION_H

namespace sge{
    enum CollisionSide : int;
    class CollisionShape;

    struct Collision{
        sge::CollisionShape *initiator;
        sge::CollisionShape *recipient;
        sge::CollisionSide initiatorImpactSide;
        sge::CollisionSide recipientImpactSide;

        friend bool operator< (const sge::Collision a, const sge::Collision b){ return a.recipient < b.recipient; }
        friend bool operator> (const sge::Collision a, const sge::Collision b){ return a.recipient > b.recipient; }
        friend bool operator== (const sge::Collision a, const sge::Collision b){ return a.recipient == b.recipient; }
        friend bool operator!= (const sge::Collision a, const sge::Collision b){ return a.recipient != b.recipient; }
    };
}

#endif
#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

namespace sge{
    class CollisionShape;
    enum CollisionSide : int;

    float determineCollisionDepth(sge::CollisionSide initiatorImpactSide, sge::CollisionShape *initiator, sge::CollisionShape *recipient);

    sge::CollisionSide determineInitiatorImpactSide(sge::CollisionShape *initiator, sge::CollisionShape *recipient);

    sge::CollisionSide flipInitiatorImpactSide(sge::CollisionSide initiatorImpactSide);
}

#endif
#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include <SFML/Graphics.hpp>

namespace sge{
    class Entity;
    struct Measurements;

    class CollisionShape : public sf::RectangleShape{
        public:
            CollisionShape(sge::Entity* ownerEntityPtr);

            sf::Vector2f offset = sf::Vector2f(0, 0);

            sge::Entity* getOwnerEntity();
            sge::Measurements getMeasurements();
            void align();

        private:
            sge::Entity* m_ownerEntityPtr;
    };
}

#endif
#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

#include <vector>

namespace sge{
    struct Collision;
    
    void resolveAABB(std::vector<sge::Collision> collisions);

    void initiatorStandOnTopOfRecipient(std::vector<sge::Collision> collisions);
}

#endif
#ifndef COLLISION_DETECTION_ALGORITHMS_H
#define COLLISION_DETECTION_ALGORITHMS_H

namespace sge{
    class CollisionShape;
    
    bool boundingBox(sge::CollisionShape* initiator, sge::CollisionShape* recipient);

    // TODO
    // bool rayRect(){}
}

#endif

#ifndef ENTITY_H
#define ENTITY_H

namespace sge{
    class PhysicalObject;
    class CollisionShape;
    class Animation;

    struct Entity{
        sge::PhysicalObject* physicalObject;
        std::unordered_map<std::string, sge::CollisionShape*> collisionShapes; 
        sge::Animation* animation = nullptr;
    };
}

#endif
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>

namespace sge{
    class Entity;
    class PhysicsManager;
    class CollisionManager;
    class TextureManager;

    class EntityManager{
        public:
            EntityManager(sge::PhysicsManager* physicsManager, sge::CollisionManager* collisionManager, sge::TextureManager* textureManager);

            void registerEntity(sge::Entity* entity);
            void registerEntities(std::vector<sge::Entity*> entities);
            // void destroyEntity(sge::Entity* entity);
            std::vector<sge::Entity*> getAllEntities();

        private:
            std::vector<sge::Entity*> m_entities;

            sge::PhysicsManager* m_physicsManagerPtr;
            sge::CollisionManager* m_collisionManagerPtr;
            sge::TextureManager* m_textureManagerPtr;

    };
}

#endif
#ifndef ENTITY_BUILDERS_H
#define ENTITY_BUILDERS_H

#include <SFML/Graphics.hpp>

namespace sge{
    class Entity;
    
    // Builds Entity that consists only of PhysicalObject
    Entity* buildPlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);

    // Builds Entity that consists of PhysicalObject* and "globalBounds" -> CollisionShape*
    Entity* buildStaticEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);

    // Builds Entity that consists of PhysicalObject* and "globalBounds" -> CollisionShape*
    //
    // PhysicalObject added continuous computations:
    // "updateVelocity" -> updateVelocityBasedOnAcceleration()
    // "updatePosition" -> updatePositionBasedOnVelocity()
    Entity* buildMobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);
}

#endif

#ifndef DEBUG_ENTITY_H
#define DEBUG_ENTITY_H

#include <SFML/Graphics.hpp> 
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

#ifndef COLLISION_SHAPE_BORDER_SETTINGS_H
#define COLLISION_SHAPE_BORDER_SETTINGS_H

#include <SFML/Graphics.hpp>

namespace sge{
    struct CollisionShapeBorderSettings{
        sf::Color color = sf::Color::Blue;
        float thickness = .5;
    };
}

#endif

namespace sge{
    class Entity;
    class CollisionShapeBorder;

    class DebugEntity{
        public:
            DebugEntity(sge::Entity* relatedEntity);

            sge::Entity* getRelatedEntity();

            bool drawCollisionShapeBorders = true;
            std::unordered_map<std::string, sge::CollisionShapeBorderSettings> customCollisionShapeBorderSettings;
            std::vector<sge::CollisionShapeBorder*> generateCollisionShapeBorders();

            void addExtraDebugFunction(std::function<void(sf::RenderWindow* windowPtr)> extraDebugFunction);
            std::vector<std::function<void(sf::RenderWindow* windowPtr)>> getExtraDebugFunctions();

        private:
            sge::Entity* m_relatedEntity;
            sge::CollisionShapeBorderSettings m_defaultCollisionShapeBorderSettings = sge::CollisionShapeBorderSettings();
            std::vector<std::function<void(sf::RenderWindow* windowPtr)>> m_extraDebugFunctions;
    };
}

#endif
#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace sge{
    class DebugEntity;

    class DebugManager{
        public:
            void registerDebugEntity(sge::DebugEntity* debugEntity);

            void showDebugInfo(sf::RenderWindow* windowPtr);

        private:
            std::vector<sge::DebugEntity*> m_debugEntities; // ? map<Entity -> DebugEntity> ?
    };
}

#endif
#ifndef COLLISION_SHAPE_BORDER_H
#define COLLISION_SHAPE_BORDER_H

#include <SFML/Graphics.hpp>

namespace sge{
    class CollisionShape;
    struct CollisionShapeBorderSettings;

    class CollisionShapeBorder : public sf::RectangleShape{
        public:
            CollisionShapeBorder(sge::CollisionShape* owner, sge::CollisionShapeBorderSettings settings);
    };
}

#endif

#ifndef APPROACH_H
#define APPROACH_H

namespace sge{
    float approach(float goal, float current, float dt){
        float diff = goal - current;

        if(diff > dt) return current + dt;
        if(diff < -dt) return current - dt;
        return goal;
    }
}

#endif
#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

namespace sge{
    struct Measurements{
        float x;
        float y;
        float height;
        float width;
    };
}

#endif

#endif

#ifndef SGE_MAIN

sge::Universe::Universe(bool DEBUG){
    sge::PhysicsManager* PM = new sge::PhysicsManager();
    sge::CollisionManager* CM = new sge::CollisionManager();
    sge::TextureManager* TM = new sge::TextureManager();
    sge::EntityManager* EM = new sge::EntityManager(PM, CM, TM);
    
    physicsManager = PM;
    collisionManager = CM;
    textureManager = TM;
    entityManager = EM;

    if(DEBUG){
        debugManager = new sge::DebugManager();
    }
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

        if(debugManager){
            debugManager->showDebugInfo(m_windowPtr);
        }
        //

        m_windowPtr->display();
    }
}


sge::TextureSheet::TextureSheet(sge::TextureSheetSizes textureSheetSizes, std::string location){
    m_location = location;
    m_textureSheet.loadFromFile(location);

    for(int i = 0; i < textureSheetSizes.numTexturesY*textureSheetSizes.textureSizeY; i += textureSheetSizes.textureSizeY){
        for(int j = 0; j < textureSheetSizes.numTexturesX*textureSheetSizes.textureSizeX; j += textureSheetSizes.textureSizeX){
            m_textureRects.push_back(sf::IntRect(j, i, textureSheetSizes.textureSizeX, textureSheetSizes.textureSizeY));
        }
    }
}

std::string sge::TextureSheet::getLocation(){ return m_location; }
sf::Texture* sge::TextureSheet::getTextureSheet(){ return &m_textureSheet; }
sf::IntRect sge::TextureSheet::getTextureRect(int textureN){ return m_textureRects[textureN]; }


void sge::TextureManager::loadTexture(std::string location, std::string name, sge::TextureSheetSizes textureSheetSizes){ m_loadedTextures[name] = new sge::TextureSheet(textureSheetSizes, location); }
sge::TextureSheet* sge::TextureManager::getTexture(std::string name){ return m_loadedTextures[name]; }

void sge::TextureManager::registerAnimation(sge::Animation* animation){ m_animations.push_back(animation); }
void sge::TextureManager::deregisterAnimation(sge::Animation* animation){ m_animations.erase(std::remove(m_animations.begin(), m_animations.end(), animation), m_animations.end()); }

void sge::TextureManager::initAnimationClocks(){
    for(sge::Animation* animation : m_animations){
        animation->restartClock();
    }
}

void sge::TextureManager::updateAnimations(){
    for(sge::Animation* animation : m_animations){
        animation->run();
    }
}


sge::Animation::Animation(sge::TextureSheet* textureSheet, sf::Sprite* owner, int initialTextureN){
    m_textureSheet = textureSheet;
    m_owner = owner;
    
    m_owner->setTexture(*textureSheet->getTextureSheet());
    m_owner->setTextureRect(textureSheet->getTextureRect(initialTextureN));
}

void sge::Animation::addTextureSequence(std::string name, std::vector<int> textureSequence){ m_textureSequences[name] = textureSequence; }
void sge::Animation::setCurrentTextureSequence(std::string name){
    if(m_currentTextureSequence != name){
        m_currentTextureSequence = name;
        m_currentTextureN = 0;
        m_clock.restart();
    }
}

void sge::Animation::run(){
    if(!m_textureSequences.size()){
        printf("No texture sequences initialized.\n");
        exit(1);
    }
    if(!m_currentTextureSequence.length()){
        printf("Can not run animation if no current texture sequence is set.\n"); // ? Default to first added ?
        exit(1);
    }

    // TODO dynamic animation delay (for each animation ?)
    if(m_clock.getElapsedTime().asMilliseconds() > 100){
        m_owner->setTextureRect(m_textureSheet->getTextureRect(m_textureSequences[m_currentTextureSequence].at(m_currentTextureN)));
        
        if(m_currentTextureN+1 == m_textureSequences[m_currentTextureSequence].size()){
            m_currentTextureN = 0;
        }
        else m_currentTextureN++;

        
        m_clock.restart();
    }
}
void sge::Animation::restartClock(){ m_clock.restart(); }

void sge::PhysicsManager::registerPhysicalObject(sge::PhysicalObject* physicalObject){ m_physicalObjects.push_back(physicalObject); }
void sge::PhysicsManager::deregisterPhysicalObject(sge::PhysicalObject* physicalObject){ m_physicalObjects.erase(std::remove(m_physicalObjects.begin(), m_physicalObjects.end(), physicalObject), m_physicalObjects.end()); }
std::vector<sge::PhysicalObject*> sge::PhysicsManager::getAllPhysicalObjects(){ return m_physicalObjects; }

void sge::PhysicsManager::updatePhysics(float dt){
    for(sge::PhysicalObject* physicalObject : m_physicalObjects){
        physicalObject->update(dt);
    }
}


void sge::PhysicalObject::createAction(std::string name, std::function<void()> action){ m_actions[name] = action; }
void sge::PhysicalObject::doAction(std::string name){ m_actions[name](); }

void sge::PhysicalObject::createContinuousComputation(std::string name, std::function<void(sge::PhysicalObject*, float)> computation){
    m_continuousComputations[name] = computation;
    m_continuousComputationOrder.push_back(name);
}

void sge::PhysicalObject::createFlag(std::string name){ m_flags[name] = false; }
bool sge::PhysicalObject::getFlag(std::string flagName){ return m_flags[flagName]; }
void sge::PhysicalObject::setFlag(std::string flagName, bool value){ m_flags[flagName] = value; }

void sge::PhysicalObject::update(float dt){
    // Run continuous computations in order of insertion
    for(std::string computation : m_continuousComputationOrder){
        m_continuousComputations[computation](this, dt);
    }
};


std::function<void(sge::PhysicalObject*, float)> sge::updatePositionBasedOnVelocity(){
    return [](sge::PhysicalObject* thisPhysicalObject, float dt){
        thisPhysicalObject->setPosition(thisPhysicalObject->getPosition() + thisPhysicalObject->velocity * dt);
    };
}

std::function<void(sge::PhysicalObject*, float)> sge::updateVelocityBasedOnAcceleration(sf::Vector2f speedLimit){
    return [speedLimit](sge::PhysicalObject* thisPhysicalObject, float dt){
        if(abs(thisPhysicalObject->velocity.x) >= speedLimit.x){
            thisPhysicalObject->velocity.x = speedLimit.x;
        }
        else{
            thisPhysicalObject->velocity.x += thisPhysicalObject->acceleration.x;
        }

        if(abs(thisPhysicalObject->velocity.y) >= speedLimit.y){
            thisPhysicalObject->velocity.y = speedLimit.y;
        }
        else{
            thisPhysicalObject->velocity.y += thisPhysicalObject->acceleration.y;
        }
    };
}


void sge::CollisionManager::registerCollisionShape(sge::CollisionShape* collisionShape){ m_allCollisionShapes.push_back(collisionShape); }
void sge::CollisionManager::deregisterCollisionShape(sge::CollisionShape* collisionShape){ m_allCollisionShapes.erase(std::remove(m_allCollisionShapes.begin(), m_allCollisionShapes.end(), collisionShape), m_allCollisionShapes.end()); }
void sge::CollisionManager::registerCollisionShapes(std::vector<sge::CollisionShape*> collisionShapes){ m_allCollisionShapes.insert(m_allCollisionShapes.end(), collisionShapes.begin(), collisionShapes.end()); }
void sge::CollisionManager::degisterCollisionShapes(std::vector<sge::CollisionShape*> collisionShapes){
    for(sge::CollisionShape* collisionShape : collisionShapes){
        deregisterCollisionShape(collisionShape);
    }
}
std::vector<sge::CollisionShape*> sge::CollisionManager::getAllCollisionShapes(){ return m_allCollisionShapes; }
void sge::CollisionManager::alignCollisionShapes(){
    for(sge::CollisionShape* collisionShape : m_allCollisionShapes){
        collisionShape->align();
    }
}

void sge::CollisionManager::registerCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionGroup){ m_collisionGroups[name] = collisionGroup; } 
void sge::CollisionManager::deregisterCollisionGroup(std::string name){ m_collisionGroups.erase(name); }
void sge::CollisionManager::registerCollisionGroups(std::unordered_map<std::string, std::vector<sge::CollisionShape*>> collisionGroups){ m_collisionGroups.insert(collisionGroups.begin(), collisionGroups.end()); }
void sge::CollisionManager::deregisterCollisionGroups(std::unordered_map<std::string, std::vector<sge::CollisionShape*>> collisionGroups){
    for(auto& [name, _] : collisionGroups){
        deregisterCollisionGroup(name);
    }
}
std::unordered_map<std::string, std::vector<sge::CollisionShape*>> sge::CollisionManager::getCollisionGroups(){ return m_collisionGroups; }

void sge::CollisionManager::createCollisionPair(std::string name, std::string initiatorGroup, std::string recipientGroup){
    if(!m_collisionGroups.count(initiatorGroup) && !m_collisionGroups.count(recipientGroup)){
        printf("Can not create %s - %s collision m_collisionPairs[pair].", initiatorGroup.c_str(), recipientGroup.c_str());
        exit(1);
    }

    m_collisionPairs[name] = new sge::CollisionPair{std::make_pair(initiatorGroup, recipientGroup)};
    m_collisionPairsOrder.push_back(name);
}
void sge::CollisionManager::setPairCollisionDetectionAlgorithm(std::string collisionPairName, std::function<bool(sge::CollisionShape*, sge::CollisionShape*)> collisionDetectionAlgorithm){ m_collisionPairs[collisionPairName]->checkCollision = collisionDetectionAlgorithm; }
void sge::CollisionManager::setPairCollisionResponse(std::string collisionPairName, std::string collisionPhase, std::function<void(std::vector<sge::Collision>)> response){
    if(collisionPhase == "start_phase"){
        m_collisionPairs[collisionPairName]->startPhaseCollisionResponse = response;
    }
    else if(collisionPhase == "continuous_phase"){
        m_collisionPairs[collisionPairName]->continuousPhaseCollisionResponse = response;
    }
    else if(collisionPhase == "end_phase"){
        m_collisionPairs[collisionPairName]->endPhaseCollisionResponse = response;
    }
}

void sge::CollisionManager::updateCollisions(){
    std::vector<sge::Collision> presentCollisions;

    // TODO check in order of insertion ?
    for(std::string pair : m_collisionPairsOrder){

        for(sge::CollisionShape* initiator : m_collisionGroups[m_collisionPairs[pair]->collisionGroups.first]){
            // Register all present collisions
            for(sge::CollisionShape* recipient : m_collisionGroups[m_collisionPairs[pair]->collisionGroups.second]){
                if(m_collisionPairs[pair]->checkCollision(initiator, recipient)){
                    CollisionSide initiatorImpactSide = determineInitiatorImpactSide(initiator, recipient);

                    presentCollisions.push_back(sge::Collision{
                        initiator,
                        recipient,
                        initiatorImpactSide,
                        flipInitiatorImpactSide(initiatorImpactSide)
                    });
                }
            }
            //

            std::vector<sge::Collision> pastCollisions = m_collisionPairs[pair]->pastCollisions[initiator];

            // Determine collision phase
            std::sort(presentCollisions.begin(), presentCollisions.end());
            std::sort(pastCollisions.begin(), pastCollisions.end());

            // std::vector<sge::Collision> startPhaseCollisions;
            // std::set_difference(presentCollisions.begin(),presentCollisions.end(), pastCollisions.begin(),pastCollisions.end(), std::back_inserter(startPhaseCollisions));

            // std::vector<sge::Collision> continuousPhaseCollisions;
            // std::set_intersection(pastCollisions.begin(),pastCollisions.end(), presentCollisions.begin(),presentCollisions.end(), std::back_inserter(continuousPhaseCollisions));

            // std::vector<sge::Collision> endPhaseCollisions;
            // std::set_difference(pastCollisions.begin(),pastCollisions.end(), presentCollisions.begin(),presentCollisions.end(), std::back_inserter(endPhaseCollisions));

            // Either works

            std::vector<sge::Collision> continuousPhaseCollisions;
            std::set_intersection(pastCollisions.begin(),pastCollisions.end(), presentCollisions.begin(),presentCollisions.end(), std::back_inserter(continuousPhaseCollisions));

            std::vector<sge::Collision> startPhaseCollisions;
            std::set_difference(presentCollisions.begin(),presentCollisions.end(), continuousPhaseCollisions.begin(),continuousPhaseCollisions.end(), std::back_inserter(startPhaseCollisions));

            std::vector<sge::Collision> endPhaseCollisions;
            std::set_difference(pastCollisions.begin(),pastCollisions.end(), continuousPhaseCollisions.begin(),continuousPhaseCollisions.end(), std::back_inserter(endPhaseCollisions));
            //

            // Run collision responses based on collision phase
            if(startPhaseCollisions.size())
                if(m_collisionPairs[pair]->startPhaseCollisionResponse)
                    m_collisionPairs[pair]->startPhaseCollisionResponse(startPhaseCollisions);

            if(continuousPhaseCollisions.size())
                if(m_collisionPairs[pair]->continuousPhaseCollisionResponse)
                    m_collisionPairs[pair]->continuousPhaseCollisionResponse(continuousPhaseCollisions);
            
            if(endPhaseCollisions.size())
                if(m_collisionPairs[pair]->endPhaseCollisionResponse)
                    m_collisionPairs[pair]->endPhaseCollisionResponse(endPhaseCollisions);
            //

            // Reset
            m_collisionPairs[pair]->pastCollisions[initiator] = presentCollisions;
            presentCollisions.clear();
            //
        }
    }
}
#include <limits>

float sge::determineCollisionDepth(sge::CollisionSide initiatorImpactSide, sge::CollisionShape *initiator, sge::CollisionShape *recipient){
    auto [x1, y1, height1, width1] = initiator->getMeasurements();
    auto [x2, y2, height2, width2] = recipient->getMeasurements();
    
    if(initiatorImpactSide == sge::CollisionSide::left) return x2 + width2 - x1;
    if(initiatorImpactSide == sge::CollisionSide::right) return x1 + width1 - x2;
    if(initiatorImpactSide == sge::CollisionSide::top) return y2 + height2 - y1;
    if(initiatorImpactSide == sge::CollisionSide::bottom) return y1 + height1 - y2;

    return 0;
}

sge::CollisionSide sge::determineInitiatorImpactSide(sge::CollisionShape *initiator, sge::CollisionShape *recipient){
    std::vector<sge::CollisionSide> allImpactSides;

    if(initiator->getPosition().x > recipient->getPosition().x) allImpactSides.push_back(sge::CollisionSide::left);
    if(initiator->getPosition().x < recipient->getPosition().x) allImpactSides.push_back(sge::CollisionSide::right);
    if(initiator->getPosition().y > recipient->getPosition().y) allImpactSides.push_back(sge::CollisionSide::top);
    if(initiator->getPosition().y < recipient->getPosition().y) allImpactSides.push_back(sge::CollisionSide::bottom);

    sge::CollisionSide lowestDepthSide;
    float lowestDepth = std::numeric_limits<float>::infinity();
    
    for(sge::CollisionSide collisionSide : allImpactSides){
        float depth = sge::determineCollisionDepth(collisionSide, initiator, recipient);
        if(depth <= lowestDepth){
            lowestDepthSide = collisionSide;
            lowestDepth = depth;
        }
    }

    return lowestDepthSide;
}

sge::CollisionSide sge::flipInitiatorImpactSide(sge::CollisionSide initiatorImpactSide){
    if(initiatorImpactSide == sge::CollisionSide::top) return sge::CollisionSide::bottom;
    if(initiatorImpactSide == sge::CollisionSide::bottom) return sge::CollisionSide::top;
    if(initiatorImpactSide == sge::CollisionSide::right) return sge::CollisionSide::left;
    if(initiatorImpactSide == sge::CollisionSide::left) return sge::CollisionSide::right;

    return sge::CollisionSide::bottom;
}


sge::CollisionShape::CollisionShape(sge::Entity* ownerEntityPtr){
    m_ownerEntityPtr = ownerEntityPtr;

    this->setFillColor(sf::Color(0,0,0,0));
    this->setSize(sf::Vector2f(ownerEntityPtr->physicalObject->getGlobalBounds().width, ownerEntityPtr->physicalObject->getGlobalBounds().height));
}

sge::Entity* sge::CollisionShape::getOwnerEntity(){ return m_ownerEntityPtr; }
sge::Measurements sge::CollisionShape::getMeasurements(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}
void sge::CollisionShape::align(){
    this->setPosition(m_ownerEntityPtr->physicalObject->getPosition() + offset);
}


void sge::resolveAABB(std::vector<sge::Collision> collisions){
    for(sge::Collision collision : collisions){
        sge::PhysicalObject *initiatorPhysicalObject = collision.initiator->getOwnerEntity()->physicalObject;
        sge::PhysicalObject *recipientPhysicalObject = collision.recipient->getOwnerEntity()->physicalObject;
        
        // Align initiator based on impact side
        if(collision.initiatorImpactSide == sge::CollisionSide::left){
            initiatorPhysicalObject->setPosition(
                recipientPhysicalObject->getPosition().x + recipientPhysicalObject->getGlobalBounds().width - collision.initiator->offset.x,
                initiatorPhysicalObject->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::right){
            initiatorPhysicalObject->setPosition(
                recipientPhysicalObject->getPosition().x - collision.initiator->getGlobalBounds().width - collision.initiator->offset.x,
                initiatorPhysicalObject->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::top){
            initiatorPhysicalObject->setPosition(
                initiatorPhysicalObject->getPosition().x,
                recipientPhysicalObject->getPosition().y + recipientPhysicalObject->getGlobalBounds().height - collision.initiator->offset.y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::bottom){
            initiatorPhysicalObject->setPosition(
                initiatorPhysicalObject->getPosition().x,
                recipientPhysicalObject->getPosition().y - collision.initiator->getGlobalBounds().height - collision.initiator->offset.y
            );
        }
        //
    }
}

void sge::initiatorStandOnTopOfRecipient(std::vector<sge::Collision> collisions){
    for(sge::Collision collision : collisions){
        if(collision.initiatorImpactSide == sge::CollisionSide::bottom){
            collision.initiator->getOwnerEntity()->physicalObject->velocity.y = 0;
        }
    }
}


bool sge::boundingBox(sge::CollisionShape* initiator, sge::CollisionShape* recipient){
    return initiator->getGlobalBounds().intersects(recipient->getGlobalBounds());
}


sge::EntityManager::EntityManager(sge::PhysicsManager* physicsManager, sge::CollisionManager* collisionManager, sge::TextureManager* textureManager){
    m_physicsManagerPtr = physicsManager;
    m_collisionManagerPtr = collisionManager;
    m_textureManagerPtr = textureManager;
}

void sge::EntityManager::registerEntity(sge::Entity* entity){
    m_physicsManagerPtr->registerPhysicalObject(entity->physicalObject);
        
    if(entity->collisionShapes.size()){
        for(auto& [_, collisionShape] : entity->collisionShapes){
            m_collisionManagerPtr->registerCollisionShape(collisionShape);
        }
    }
    
    if(entity->animation){
        m_textureManagerPtr->registerAnimation(entity->animation);
    }

    m_entities.push_back(entity);
}

void sge::EntityManager::registerEntities(std::vector<sge::Entity*> entities){
    for(sge::Entity* entity : entities){
        registerEntity(entity);
    }
}

std::vector<sge::Entity*> sge::EntityManager::getAllEntities(){ return m_entities; }


sge::Entity* sge::buildPlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    sge::Entity* e = new sge::Entity{ new sge::PhysicalObject() };
    e->physicalObject->setTexture(*texture);
    e->physicalObject->setTextureRect(textureRect);
    e->physicalObject->setPosition(position);

    return e;
}

sge::Entity* sge::buildStaticEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    sge::Entity* e = sge::buildPlainEntity(texture, textureRect, position);

    e->collisionShapes["globalBounds"] = new sge::CollisionShape(e);

    return e;
}

sge::Entity* sge::buildMobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    sge::Entity* e = sge::buildStaticEntity(texture, textureRect, position);

    e->physicalObject->createContinuousComputation("updateVelocity", sge::updateVelocityBasedOnAcceleration());
    e->physicalObject->createContinuousComputation("updatePosition", sge::updatePositionBasedOnVelocity());

    return e;
}


sge::DebugEntity::DebugEntity(sge::Entity* relatedEntity){ m_relatedEntity = relatedEntity; }

sge::Entity* sge::DebugEntity::getRelatedEntity(){ return m_relatedEntity; }

std::vector<sge::CollisionShapeBorder*> sge::DebugEntity::generateCollisionShapeBorders(){
    std::vector<sge::CollisionShapeBorder*> collisionShapeBorders;
    for(auto &[name, collisionShape] : m_relatedEntity->collisionShapes){
        if(customCollisionShapeBorderSettings.count(name)){
            collisionShapeBorders.push_back(new sge::CollisionShapeBorder(collisionShape, customCollisionShapeBorderSettings[name]));
        }
        else{
            collisionShapeBorders.push_back(new sge::CollisionShapeBorder(collisionShape, m_defaultCollisionShapeBorderSettings));
        }
    }

    return collisionShapeBorders;
}

void sge::DebugEntity::addExtraDebugFunction(std::function<void(sf::RenderWindow* windowPtr)> extraDebugFunction){ m_extraDebugFunctions.push_back(extraDebugFunction); }
std::vector<std::function<void(sf::RenderWindow* windowPtr)>> sge::DebugEntity::getExtraDebugFunctions(){ return m_extraDebugFunctions; }


void sge::DebugManager::registerDebugEntity(sge::DebugEntity* debugEntity){ m_debugEntities.push_back(debugEntity); }

void sge::DebugManager::showDebugInfo(sf::RenderWindow* windowPtr){
    for(sge::DebugEntity* debugEntity : m_debugEntities){
        // Run extraDebugFunctions
        for(std::function<void(sf::RenderWindow* renderWindow)> extraDebugFunction : debugEntity->getExtraDebugFunctions()){
            extraDebugFunction(windowPtr);
        }
        //

        // Draw collision shape borders
        if(debugEntity->drawCollisionShapeBorders){
            for(sge::CollisionShapeBorder* collisionShapeBorder : debugEntity->generateCollisionShapeBorders()){
                windowPtr->draw(*collisionShapeBorder);
            }
        }
        //
    }
}


sge::CollisionShapeBorder::CollisionShapeBorder(sge::CollisionShape* owner, sge::CollisionShapeBorderSettings settings){
    this->setFillColor(sf::Color(0,0,0,0));

    this->setOutlineColor(settings.color);
    this->setOutlineThickness(settings.thickness);

    this->setPosition(sf::Vector2f(owner->getPosition().x + settings.thickness, owner->getPosition().y + settings.thickness));
    this->setSize(sf::Vector2f(owner->getSize().x - settings.thickness*2, owner->getSize().y - settings.thickness*2));
}


#endif