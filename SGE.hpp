namespace sge{

#ifndef SGE_HPP
#define SGE_HPP

#include <SFML/Graphics.hpp>

#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <SFML/Graphics.hpp>
#ifndef CONTINUOUS_COMPUTATION_H
#define CONTINUOUS_COMPUTATION_H

struct ContinuousComputation{
    bool shouldRun;
    std::function<void(float dt)> compute;
};

#endif

class PhysicalObject : public sf::Sprite{
    public:
        sf::Vector2f velocity = sf::Vector2f(0, 0);
        sf::Vector2f acceleration = sf::Vector2f(0, 0);
        sf::Vector2f speedLimit = sf::Vector2f(9999,9999);

        void createAction(std::string name, std::function<void()> action);
        void doAction(std::string name);
        // removeAction()

        void createContinuousComputation(std::string name, std::function<void(float dt)> computation);
        void runContinuousComputation(std::string name);
        void stopContinuousComputation(std::string name);
        

        void createFlag(std::string name);
        bool getFlag(std::string flagName);
        void setFlag(std::string flagName, bool value);        
        // removeflag()

        void update(float dt);

    private:
        std::unordered_map<std::string, std::function<void()>> m_actions;
        std::unordered_map<std::string, ContinuousComputation> m_continuousComputations;
        std::vector<std::string> m_continuousComputationOrder;
        std::unordered_map<std::string, bool> m_flags;
};

#endif

class PhysicsManager{
    public:
        void registerPhysicalObject(PhysicalObject* physicalObject);
        void deregisterPhysicalObject(PhysicalObject* physicalObject);
        std::vector<PhysicalObject*> getAllPhysicalObjects();

        void updatePhysics(float dt);

    private:
        std::vector<PhysicalObject*> m_physicalObjects;
};

#endif

#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

struct Collision;
struct CollisionPair;
class CollisionShape;

class CollisionManager{
    public:
        void registerCollisionShape(CollisionShape* collisionShape);
        void deregisterCollisionShape(CollisionShape* collisionShape);
        void registerCollisionShapes(std::vector<CollisionShape*> collisionShapes);
        void degisterCollisionShapes(std::vector<CollisionShape*> collisionShapes);
        std::vector<CollisionShape*> getAllCollisionShapes();
        void alignCollisionShapes();

        void registerCollisionGroup(std::string name, std::vector<CollisionShape*> collisionGroup);
        void deregisterCollisionGroup(std::string name);
        void registerCollisionGroups(std::unordered_map<std::string, std::vector<CollisionShape*>> collisionGroups);
        void deregisterCollisionGroups(std::unordered_map<std::string, std::vector<CollisionShape*>> collisionGroups);
        std::unordered_map<std::string, std::vector<CollisionShape*>> getCollisionGroups();

        void createCollisionPair(std::string name, std::string initiatorGroup, std::string recipientGroup);
        void setPairCollisionDetectionAlgorithm(std::string collisionPairName, std::function<bool(CollisionShape* initiator, CollisionShape* recipient)> collisionDetectionAlgorithm);
        void setPairCollisionResponse(std::string collisionPairName, std::string collisionPhase, std::function<void(std::vector<Collision>)> response);

        void updateCollisions();

    private:
        std::vector<CollisionShape*> m_allCollisionShapes;
        std::unordered_map<std::string, std::vector<CollisionShape*>> m_collisionGroups;
        std::unordered_map<std::string, CollisionPair*> m_collisionPairs;
        std::vector<std::string> m_collisionPairsOrder;
};

#endif
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#ifndef TEXTURE_SHEET_SIZES_H
#define TEXTURE_SHEET_SIZES_H

struct TextureSheetSizes{
    int textureSizeX;
    int textureSizeY;
    int numTexturesX;
    int numTexturesY;
};

#endif
#ifndef TEXTURESHEET_H
#define TEXTURESHEET_H

#include <SFML/Graphics.hpp>

// TODO texturesheet with gaps between textures
// ? parse from .tsx ?
class TextureSheet{
    public:
        TextureSheet(TextureSheetSizes textureSheetSizes, std::string location);

        std::string getLocation();
        sf::Texture* getTextureSheet();
        sf::IntRect getTextureRect(int textureN);

    private:
        std::string m_location;
        sf::Texture m_textureSheet;
        std::vector<sf::IntRect> m_textureRects;
};

#endif
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

// TODO Animations should switch immediately
class Animation{
    public:
        Animation(TextureSheet* textureSheet, sf::Sprite* owner, int initialTextureN);
    
        
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
        TextureSheet* m_textureSheet;
        
        sf::Clock m_clock;
        std::unordered_map<std::string, std::vector<int>> m_textureSequences; // e.g. "idle": [5, 6, 7, 8]
        std::string m_currentTextureSequence;
        int m_currentTextureN = 0;

};

#endif

class TextureManager{
    public:
        void loadTexture(std::string location, std::string name, TextureSheetSizes textureSheetSizes);
        TextureSheet* getTexture(std::string name);

        void registerAnimation(Animation* animation);
        void deregisterAnimation(Animation* animation);

        void initAnimationClocks();
        void updateAnimations();

    private:
        std::unordered_map<std::string, TextureSheet*> m_loadedTextures;
        std::vector<Animation*> m_animations;
};

#endif
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#ifndef ENTITY_H
#define ENTITY_H

#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include <SFML/Graphics.hpp>
class Entity;
struct Measurements;

class CollisionShape : public sf::RectangleShape{
    public:
        CollisionShape(Entity* ownerEntityPtr);

        sf::Vector2f offset = sf::Vector2f(0, 0);

        Entity* getOwnerEntity();
        Measurements getMeasurements();
        void align();

    private:
        Entity* m_ownerEntityPtr;
};

#endif

struct Entity{
    PhysicalObject* physicalObject;
    std::unordered_map<std::string, CollisionShape*> collisionShapes; 
    Animation* animation = nullptr;
};

#endif

class EntityManager{
    public:
        EntityManager(PhysicsManager* physicsManager, CollisionManager* collisionManager, TextureManager* textureManager);

        void registerEntity(Entity* entity);
        void registerEntities(std::vector<Entity*> entities);
        void destroyEntity(Entity* entity);
        // void destroyEntityGroup(std::string name);
        std::vector<Entity*> getAllEntities();

    private:
        std::vector<Entity*> m_entities;

        PhysicsManager* m_physicsManagerPtr;
        CollisionManager* m_collisionManagerPtr;
        TextureManager* m_textureManagerPtr;

};

#endif
#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#ifndef DEBUG_ENTITY_H
#define DEBUG_ENTITY_H

#ifndef COLLISION_SHAPE_BORDER_H
#define COLLISION_SHAPE_BORDER_H

#ifndef COLLISION_SHAPE_BORDER_SETTINGS_H
#define COLLISION_SHAPE_BORDER_SETTINGS_H

#include <SFML/Graphics.hpp>

struct CollisionShapeBorderSettings{
    sf::Color color = sf::Color::Blue;
    float thickness = .5;
};

#endif

class CollisionShapeBorder : public sf::RectangleShape{
    public:
        CollisionShapeBorder(CollisionShape* owner, CollisionShapeBorderSettings settings);
};

#endif

class DebugEntity{
    public:
        DebugEntity(Entity* relatedEntity);

        bool drawCollisionShapeBorders = true;
        std::unordered_map<std::string, CollisionShapeBorderSettings> customCollisionShapeBorderSettings;
        std::vector<CollisionShapeBorder*> generateCollisionShapeBorders();

        void addExtraDebugFunction(std::function<void(sf::RenderWindow* windowPtr)> extraDebugFunction);
        std::vector<std::function<void(sf::RenderWindow* windowPtr)>> getExtraDebugFunctions();

    private:
        Entity* m_relatedEntity;
        CollisionShapeBorderSettings m_defaultCollisionShapeBorderSettings = CollisionShapeBorderSettings();
        std::vector<std::function<void(sf::RenderWindow* windowPtr)>> m_extraDebugFunctions;
};

#endif

class DebugManager{
    public:
        void registerDebugEntity(DebugEntity* debugEntity);

        void showDebugInfo(sf::RenderWindow* windowPtr);

    private:
        std::vector<DebugEntity*> m_debugEntities; // ? map<Entity -> DebugEntity> ?
};

#endif

class Universe{
    public:
        Universe(bool DEBUG = false);

        void setupWindow(sf::RenderWindow* window);

        void addController(std::function<void()> controller);
        void addEventHandler(std::function<void(sf::Event event)> eventHandler);

        void loop();

        PhysicsManager* physicsManager = nullptr;
        CollisionManager* collisionManager = nullptr;
        TextureManager* textureManager = nullptr;
        EntityManager* entityManager = nullptr;
        DebugManager* debugManager = nullptr;

    private:
        sf::RenderWindow* m_windowPtr;

        sf::Clock m_deltaClock;
        
        std::vector<std::function<void()>> m_controllers;
        std::vector<std::function<void(sf::Event event)>> m_eventHandlers;
};

#endif

#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

std::function<void(float)> updatePositionBasedOnVelocity(PhysicalObject* physicalObject){
    return [physicalObject](float dt){
        physicalObject->setPosition(physicalObject->getPosition() + physicalObject->velocity * dt);
    };
}

std::function<void(float)> updateVelocityBasedOnAcceleration(PhysicalObject* physicalObject){
    return [physicalObject](float dt){
        if(abs(physicalObject->velocity.x) >= physicalObject->speedLimit.x){
            physicalObject->velocity.x = physicalObject->speedLimit.x;
        }
        else{
            physicalObject->velocity.x += physicalObject->acceleration.x;
        }

        if(abs(physicalObject->velocity.y) >= physicalObject->speedLimit.y){
            physicalObject->velocity.y = physicalObject->speedLimit.y;
        }
        else{
            physicalObject->velocity.y += physicalObject->acceleration.y;
        }
    };
}

#endif

#ifndef COLLISION_PAIR_H
#define COLLISION_PAIR_H

struct Collision;
class CollisionShape;

struct CollisionPair{
    std::pair<std::string, std::string> collisionGroups;
    
    std::function<void(std::vector<Collision>)> startPhaseCollisionResponse;
    std::function<void(std::vector<Collision>)> continuousPhaseCollisionResponse;
    std::function<void(std::vector<Collision>)> endPhaseCollisionResponse;

    std::unordered_map<CollisionShape*, std::vector<Collision>> pastCollisions;
    
    std::function<bool(CollisionShape *initiator, CollisionShape *recipient)> checkCollision;
};

#endif
#ifndef COLLISION_SIDE_H
#define COLLISION_SIDE_H

enum CollisionSide : int{ left, right, top, bottom };

#endif
#ifndef COLLISION_H
#define COLLISION_H

enum CollisionSide : int;
class CollisionShape;

struct Collision{
    CollisionShape *initiator;
    CollisionShape *recipient;
    CollisionSide initiatorImpactSide;
    CollisionSide recipientImpactSide;

    friend bool operator< (const Collision a, const Collision b);
    friend bool operator> (const Collision a, const Collision b);
    friend bool operator== (const Collision a, const Collision b);
    friend bool operator!= (const Collision a, const Collision b);
};

#endif
#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

class CollisionShape;
enum CollisionSide : int;

float determineCollisionDepth(CollisionSide initiatorImpactSide, CollisionShape *initiator, CollisionShape *recipient);

CollisionSide determineInitiatorImpactSide(CollisionShape *initiator, CollisionShape *recipient);

CollisionSide flipInitiatorImpactSide(CollisionSide initiatorImpactSide);

#endif

#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

#include <vector>
struct Collision;

void resolveAABB(std::vector<Collision> collisions);

void initiatorStandOnTopOfRecipient(std::vector<Collision> collisions);

#endif
#ifndef COLLISION_DETECTION_ALGORITHMS_H
#define COLLISION_DETECTION_ALGORITHMS_H

class CollisionShape;

bool boundingBox(CollisionShape* initiator, CollisionShape* recipient);

// TODO
// bool rayRect(){}

#endif

#ifndef ENTITY_BUILDERS_H
#define ENTITY_BUILDERS_H

// Plain entity - Entity that consists only of PhysicalObject
Entity* buildPlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    Entity* e = new Entity{ new PhysicalObject() };
    e->physicalObject->setTexture(*texture);
    e->physicalObject->setTextureRect(textureRect);
    e->physicalObject->setPosition(position);

    return e;
}

// Static entity - Plain entity that has >= 1 CollisionShape(s)
Entity* buildStaticEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    Entity* e = buildPlainEntity(texture, textureRect, position);

    e->collisionShapes["globalBounds"] = new CollisionShape(e);

    return e;
}

// Mobile entity - Static entity that has calculations that allow mobility
Entity* buildMobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    Entity* e = buildStaticEntity(texture, textureRect, position);

    e->physicalObject->createContinuousComputation("updateVelocity", updateVelocityBasedOnAcceleration(e->physicalObject));
    e->physicalObject->createContinuousComputation("updatePosition", updatePositionBasedOnVelocity(e->physicalObject));

    return e;
}

#endif

#ifndef APPROACH_H
#define APPROACH_H

float approach(float goal, float current, float dt){
    float diff = goal - current;

    if(diff > dt) return current + dt;
    if(diff < -dt) return current - dt;
    return goal;
}

#endif
#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

struct Measurements{
    float x;
    float y;
    float height;
    float width;
};

#endif

#endif

#ifndef SGE_MAIN

void PhysicalObject::createAction(std::string name, std::function<void()> action){ m_actions[name] = action; }
void PhysicalObject::doAction(std::string name){ m_actions[name](); }

void PhysicalObject::createContinuousComputation(std::string name, std::function<void(float dt)> computation){
    m_continuousComputations[name] = { true, computation };
    m_continuousComputationOrder.push_back(name);
}
void PhysicalObject::runContinuousComputation(std::string name){ m_continuousComputations[name].shouldRun = true; }
void PhysicalObject::stopContinuousComputation(std::string name){ m_continuousComputations[name].shouldRun = false; }

void PhysicalObject::createFlag(std::string name){ m_flags[name] = false; }
bool PhysicalObject::getFlag(std::string flagName){ return m_flags[flagName]; }
void PhysicalObject::setFlag(std::string flagName, bool value){ m_flags[flagName] = value; }

void PhysicalObject::update(float dt){
    // Run continuous computations in order of insertion
    for(std::string computation : m_continuousComputationOrder){
        if(m_continuousComputations[computation].shouldRun){
            m_continuousComputations[computation].compute(dt);
        }
    }
};


void PhysicsManager::registerPhysicalObject(PhysicalObject* physicalObject){ m_physicalObjects.push_back(physicalObject); }
void PhysicsManager::deregisterPhysicalObject(PhysicalObject* physicalObject){ m_physicalObjects.erase(std::remove(m_physicalObjects.begin(), m_physicalObjects.end(), physicalObject), m_physicalObjects.end()); }
std::vector<PhysicalObject*> PhysicsManager::getAllPhysicalObjects(){ return m_physicalObjects; }

void PhysicsManager::updatePhysics(float dt){
    for(PhysicalObject* physicalObject : m_physicalObjects){
        physicalObject->update(dt);
    }
}


void CollisionManager::registerCollisionShape(CollisionShape* collisionShape){ m_allCollisionShapes.push_back(collisionShape); }
void CollisionManager::deregisterCollisionShape(CollisionShape* collisionShape){ m_allCollisionShapes.erase(std::remove(m_allCollisionShapes.begin(), m_allCollisionShapes.end(), collisionShape), m_allCollisionShapes.end()); }
void CollisionManager::registerCollisionShapes(std::vector<CollisionShape*> collisionShapes){ m_allCollisionShapes.insert(m_allCollisionShapes.end(), collisionShapes.begin(), collisionShapes.end()); }
void CollisionManager::degisterCollisionShapes(std::vector<CollisionShape*> collisionShapes){
    for(CollisionShape* collisionShape : collisionShapes){
        deregisterCollisionShape(collisionShape);
    }
}
std::vector<CollisionShape*> CollisionManager::getAllCollisionShapes(){ return m_allCollisionShapes; }
void CollisionManager::alignCollisionShapes(){
    for(CollisionShape* collisionShape : m_allCollisionShapes){
        collisionShape->align();
    }
}

void CollisionManager::registerCollisionGroup(std::string name, std::vector<CollisionShape*> collisionGroup){ m_collisionGroups[name] = collisionGroup; } 
void CollisionManager::deregisterCollisionGroup(std::string name){ m_collisionGroups.erase(name); }
void CollisionManager::registerCollisionGroups(std::unordered_map<std::string, std::vector<CollisionShape*>> collisionGroups){ m_collisionGroups.insert(collisionGroups.begin(), collisionGroups.end()); }
void CollisionManager::deregisterCollisionGroups(std::unordered_map<std::string, std::vector<CollisionShape*>> collisionGroups){
    for(auto& [name, _] : collisionGroups){
        deregisterCollisionGroup(name);
    }
}
std::unordered_map<std::string, std::vector<CollisionShape*>> CollisionManager::getCollisionGroups(){ return m_collisionGroups; }

void CollisionManager::createCollisionPair(std::string name, std::string initiatorGroup, std::string recipientGroup){
    if(!m_collisionGroups.count(initiatorGroup) && !m_collisionGroups.count(recipientGroup)){
        printf("Can not create %s - %s collision m_collisionPairs[pair].", initiatorGroup.c_str(), recipientGroup.c_str());
        exit(1);
    }

    m_collisionPairs[name] = new CollisionPair{std::make_pair(initiatorGroup, recipientGroup)};
    m_collisionPairsOrder.push_back(name);
}
void CollisionManager::setPairCollisionDetectionAlgorithm(std::string collisionPairName, std::function<bool(CollisionShape *CS1, CollisionShape *CS2)> collisionDetectionAlgorithm){ m_collisionPairs[collisionPairName]->checkCollision = collisionDetectionAlgorithm; }
void CollisionManager::setPairCollisionResponse(std::string collisionPairName, std::string collisionPhase, std::function<void(std::vector<Collision>)> response){
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

void CollisionManager::updateCollisions(){
    std::vector<Collision> presentCollisions;

    // TODO check in order of insertion ?
    for(std::string pair : m_collisionPairsOrder){

        for(CollisionShape* initiator : m_collisionGroups[m_collisionPairs[pair]->collisionGroups.first]){
            // Register all present collisions
            for(CollisionShape* recipient : m_collisionGroups[m_collisionPairs[pair]->collisionGroups.second]){
                if(m_collisionPairs[pair]->checkCollision(initiator, recipient)){
                    CollisionSide initiatorImpactSide = determineInitiatorImpactSide(initiator, recipient);

                    presentCollisions.push_back(Collision{
                        initiator,
                        recipient,
                        initiatorImpactSide,
                        flipInitiatorImpactSide(initiatorImpactSide)
                    });
                }
            }
            //

            std::vector<Collision> pastCollisions = m_collisionPairs[pair]->pastCollisions[initiator];

            // Determine collision phase
            std::sort(presentCollisions.begin(), presentCollisions.end());
            std::sort(pastCollisions.begin(), pastCollisions.end());

            // std::vector<Collision> startPhaseCollisions;
            // std::set_difference(presentCollisions.begin(),presentCollisions.end(), pastCollisions.begin(),pastCollisions.end(), std::back_inserter(startPhaseCollisions));

            // std::vector<Collision> continuousPhaseCollisions;
            // std::set_intersection(pastCollisions.begin(),pastCollisions.end(), presentCollisions.begin(),presentCollisions.end(), std::back_inserter(continuousPhaseCollisions));

            // std::vector<Collision> endPhaseCollisions;
            // std::set_difference(pastCollisions.begin(),pastCollisions.end(), presentCollisions.begin(),presentCollisions.end(), std::back_inserter(endPhaseCollisions));

            // Either works

            std::vector<Collision> continuousPhaseCollisions;
            std::set_intersection(pastCollisions.begin(),pastCollisions.end(), presentCollisions.begin(),presentCollisions.end(), std::back_inserter(continuousPhaseCollisions));

            std::vector<Collision> startPhaseCollisions;
            std::set_difference(presentCollisions.begin(),presentCollisions.end(), continuousPhaseCollisions.begin(),continuousPhaseCollisions.end(), std::back_inserter(startPhaseCollisions));

            std::vector<Collision> endPhaseCollisions;
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


TextureSheet::TextureSheet(TextureSheetSizes textureSheetSizes, std::string location){
    m_location = location;
    m_textureSheet.loadFromFile(location);

    for(int i = 0; i < textureSheetSizes.numTexturesY*textureSheetSizes.textureSizeY; i += textureSheetSizes.textureSizeY){
        for(int j = 0; j < textureSheetSizes.numTexturesX*textureSheetSizes.textureSizeX; j += textureSheetSizes.textureSizeX){
            m_textureRects.push_back(sf::IntRect(j, i, textureSheetSizes.textureSizeX, textureSheetSizes.textureSizeY));
        }
    }
}

std::string TextureSheet::getLocation(){ return m_location; }
sf::Texture* TextureSheet::getTextureSheet(){ return &m_textureSheet; }
sf::IntRect TextureSheet::getTextureRect(int textureN){ return m_textureRects[textureN]; }


Animation::Animation(TextureSheet* textureSheet, sf::Sprite* owner, int initialTextureN){
    m_textureSheet = textureSheet;
    m_owner = owner;
    
    m_owner->setTexture(*textureSheet->getTextureSheet());
    m_owner->setTextureRect(textureSheet->getTextureRect(initialTextureN));
}

void Animation::addTextureSequence(std::string name, std::vector<int> textureSequence){ m_textureSequences[name] = textureSequence; }
void Animation::setCurrentTextureSequence(std::string name){
    if(m_currentTextureSequence != name){
        m_currentTextureSequence = name;
        m_currentTextureN = 0;
        m_clock.restart();
    }
}

void Animation::run(){
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
void Animation::restartClock(){ m_clock.restart(); }

void TextureManager::loadTexture(std::string location, std::string name, TextureSheetSizes textureSheetSizes){ m_loadedTextures[name] = new TextureSheet(textureSheetSizes, location); }
TextureSheet* TextureManager::getTexture(std::string name){ return m_loadedTextures[name]; }

void TextureManager::registerAnimation(Animation* animation){ m_animations.push_back(animation); }
void TextureManager::deregisterAnimation(Animation* animation){ m_animations.erase(std::remove(m_animations.begin(), m_animations.end(), animation), m_animations.end()); }

void TextureManager::initAnimationClocks(){
    for(Animation* animation : m_animations){
        animation->restartClock();
    }
}

void TextureManager::updateAnimations(){
    for(Animation* animation : m_animations){
        animation->run();
    }
}


CollisionShape::CollisionShape(Entity* ownerEntityPtr){
    m_ownerEntityPtr = ownerEntityPtr;

    this->setFillColor(sf::Color(0,0,0,0));
    this->setSize(sf::Vector2f(ownerEntityPtr->physicalObject->getGlobalBounds().width, ownerEntityPtr->physicalObject->getGlobalBounds().height));
}

Entity* CollisionShape::getOwnerEntity(){ return m_ownerEntityPtr; }
Measurements CollisionShape::getMeasurements(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}
void CollisionShape::align(){
    this->setPosition(m_ownerEntityPtr->physicalObject->getPosition() + offset);
}


EntityManager::EntityManager(PhysicsManager* physicsManager, CollisionManager* collisionManager, TextureManager* textureManager){
    m_physicsManagerPtr = physicsManager;
    m_collisionManagerPtr = collisionManager;
    m_textureManagerPtr = textureManager;
}

void EntityManager::registerEntity(Entity* entity){
    m_physicsManagerPtr->registerPhysicalObject(entity->physicalObject);
        
    if(entity->collisionShapes.size()){
        for(auto& [_, collisionShape] : entity->collisionShapes){
            m_collisionManagerPtr->registerCollisionShape(collisionShape);
        }
    }
    
    if(entity->animation){
        m_textureManagerPtr->registerAnimation(entity->animation);
    }
}

void EntityManager::registerEntities(std::vector<Entity*> entities){
    for(Entity* entity : entities){
        m_physicsManagerPtr->registerPhysicalObject(entity->physicalObject);
        
        if(entity->collisionShapes.size()){
            // Map to vector
            std::vector<CollisionShape*> entityCollisionShapes;
            for(auto& [_, collisionShape] : entity->collisionShapes){
                entityCollisionShapes.push_back(collisionShape);
            }
            //
            m_collisionManagerPtr->registerCollisionShapes(entityCollisionShapes);
        }
        
        if(entity->animation){
            m_textureManagerPtr->registerAnimation(entity->animation);
        }

        m_entities.push_back(entity);
    }
}

std::vector<Entity*> EntityManager::getAllEntities(){ return m_entities; }


CollisionShapeBorder::CollisionShapeBorder(CollisionShape* owner, CollisionShapeBorderSettings settings){
    this->setFillColor(sf::Color(0,0,0,0));

    this->setOutlineColor(settings.color);
    this->setOutlineThickness(settings.thickness);

    this->setPosition(sf::Vector2f(owner->getPosition().x + settings.thickness, owner->getPosition().y + settings.thickness));
    this->setSize(sf::Vector2f(owner->getSize().x - settings.thickness*2, owner->getSize().y - settings.thickness*2));
}


DebugEntity::DebugEntity(Entity* relatedEntity){ m_relatedEntity = relatedEntity; }

std::vector<CollisionShapeBorder*> DebugEntity::generateCollisionShapeBorders(){
    std::vector<CollisionShapeBorder*> collisionShapeBorders;
    for(auto &[name, collisionShape] : m_relatedEntity->collisionShapes){
        if(customCollisionShapeBorderSettings.count(name)){
            collisionShapeBorders.push_back(new CollisionShapeBorder(collisionShape, customCollisionShapeBorderSettings[name]));
        }
        else{
            collisionShapeBorders.push_back(new CollisionShapeBorder(collisionShape, m_defaultCollisionShapeBorderSettings));
        }
    }

    return collisionShapeBorders;
}

void DebugEntity::addExtraDebugFunction(std::function<void(sf::RenderWindow* windowPtr)> extraDebugFunction){ m_extraDebugFunctions.push_back(extraDebugFunction); }
std::vector<std::function<void(sf::RenderWindow* windowPtr)>> DebugEntity::getExtraDebugFunctions(){ return m_extraDebugFunctions; }


void DebugManager::registerDebugEntity(DebugEntity* debugEntity){ m_debugEntities.push_back(debugEntity); }

void DebugManager::showDebugInfo(sf::RenderWindow* windowPtr){
    for(DebugEntity* debugEntity : m_debugEntities){
        // Run extraDebugFunctions
        for(std::function<void(sf::RenderWindow* renderWindow)> extraDebugFunction : debugEntity->getExtraDebugFunctions()){
            extraDebugFunction(windowPtr);
        }
        //

        // Draw collision shape borders
        if(debugEntity->drawCollisionShapeBorders){
            for(CollisionShapeBorder* collisionShapeBorder : debugEntity->generateCollisionShapeBorders()){
                windowPtr->draw(*collisionShapeBorder);
            }
        }
        //
    }
}


Universe::Universe(bool DEBUG){
    PhysicsManager* PM = new PhysicsManager();
    CollisionManager* CM = new CollisionManager();
    TextureManager* TM = new TextureManager();
    EntityManager* EM = new EntityManager(PM, CM, TM);
    
    physicsManager = PM;
    collisionManager = CM;
    textureManager = TM;
    entityManager = EM;

    if(DEBUG){
        debugManager = new DebugManager();
    }
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


bool operator< (const Collision a, const Collision b){ return a.recipient < b.recipient; }
bool operator> (const Collision a, const Collision b){ return a.recipient > b.recipient; }
bool operator== (const Collision a, const Collision b){ return a.recipient == b.recipient; }
bool operator!= (const Collision a, const Collision b){ return a.recipient != b.recipient; }
#include <limits>

float determineCollisionDepth(CollisionSide initiatorImpactSide, CollisionShape *initiator, CollisionShape *recipient){
    auto [x1, y1, height1, width1] = initiator->getMeasurements();
    auto [x2, y2, height2, width2] = recipient->getMeasurements();
    
    if(initiatorImpactSide == CollisionSide::left) return x2 + width2 - x1;
    if(initiatorImpactSide == CollisionSide::right) return x1 + width1 - x2;
    if(initiatorImpactSide == CollisionSide::top) return y2 + height2 - y1;
    if(initiatorImpactSide == CollisionSide::bottom) return y1 + height1 - y2;

    return 0;
}

CollisionSide determineInitiatorImpactSide(CollisionShape *initiator, CollisionShape *recipient){
    std::vector<CollisionSide> allImpactSides;

    if(initiator->getPosition().x > recipient->getPosition().x) allImpactSides.push_back(CollisionSide::left);
    if(initiator->getPosition().x < recipient->getPosition().x) allImpactSides.push_back(CollisionSide::right);
    if(initiator->getPosition().y > recipient->getPosition().y) allImpactSides.push_back(CollisionSide::top);
    if(initiator->getPosition().y < recipient->getPosition().y) allImpactSides.push_back(CollisionSide::bottom);

    CollisionSide lowestDepthSide;
    float lowestDepth = std::numeric_limits<float>::infinity();
    
    for(CollisionSide collisionSide : allImpactSides){
        float depth = determineCollisionDepth(collisionSide, initiator, recipient);
        if(depth <= lowestDepth){
            lowestDepthSide = collisionSide;
            lowestDepth = depth;
        }
    }

    return lowestDepthSide;
}

CollisionSide flipInitiatorImpactSide(CollisionSide initiatorImpactSide){
    if(initiatorImpactSide == CollisionSide::top) return CollisionSide::bottom;
    if(initiatorImpactSide == CollisionSide::bottom) return CollisionSide::top;
    if(initiatorImpactSide == CollisionSide::right) return CollisionSide::left;
    if(initiatorImpactSide == CollisionSide::left) return CollisionSide::right;

    return CollisionSide::bottom;
}


void resolveAABB(std::vector<Collision> collisions){
    for(Collision collision : collisions){
        PhysicalObject *initiatorPhysicalObject = collision.initiator->getOwnerEntity()->physicalObject;
        PhysicalObject *recipientPhysicalObject = collision.recipient->getOwnerEntity()->physicalObject;
        
        // Align initiator based on impact side
        if(collision.initiatorImpactSide == CollisionSide::left){
            initiatorPhysicalObject->setPosition(
                recipientPhysicalObject->getPosition().x + recipientPhysicalObject->getGlobalBounds().width - collision.initiator->offset.x,
                initiatorPhysicalObject->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == CollisionSide::right){
            initiatorPhysicalObject->setPosition(
                recipientPhysicalObject->getPosition().x - collision.initiator->getGlobalBounds().width - collision.initiator->offset.x,
                initiatorPhysicalObject->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == CollisionSide::top){
            initiatorPhysicalObject->setPosition(
                initiatorPhysicalObject->getPosition().x,
                recipientPhysicalObject->getPosition().y + recipientPhysicalObject->getGlobalBounds().height - collision.initiator->offset.y
            );
        }
        else if(collision.initiatorImpactSide == CollisionSide::bottom){
            initiatorPhysicalObject->setPosition(
                initiatorPhysicalObject->getPosition().x,
                recipientPhysicalObject->getPosition().y - collision.initiator->getGlobalBounds().height - collision.initiator->offset.y
            );
        }
        //
    }
}

void initiatorStandOnTopOfRecipient(std::vector<Collision> collisions){
    for(Collision collision : collisions){
        if(collision.initiatorImpactSide == CollisionSide::bottom){
            collision.initiator->getOwnerEntity()->physicalObject->velocity.y = 0;
        }
    }
}


bool boundingBox(CollisionShape* initiator, CollisionShape* recipient){
    return initiator->getGlobalBounds().intersects(recipient->getGlobalBounds());
}


#endif

}