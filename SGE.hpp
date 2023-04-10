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
#ifndef CONTINUOUS_ACTION_H
#define CONTINUOUS_ACTION_H

struct ContinuousAction{
    bool shouldRun;
    std::function<void(float dt)> runAction;
};

#endif
#ifndef CONDITIONAL_ACTION_H
#define CONDITIONAL_ACTION_H

struct ConditionalAction{
    std::function<bool()> condition;
    std::function<void()> runAction;
};

#endif

class PhysicalObject : public sf::Sprite{
    public:
        sf::Vector2f velocity = sf::Vector2f(0, 0);
        sf::Vector2f acceleration = sf::Vector2f(0, 0);
        sf::Vector2f speedLimit = sf::Vector2f(9999,9999);

        // * Actions
        void createAction(std::string _name, std::function<void()> _action);
        void doAction(std::string actionName);

        void createContinuousAction(std::string _name, std::function<void(float dt)> _action);
        void runContinuousAction(std::string continuousActonName);
        void stopContinuousAction(std::string continuousActonName);
        
        void createConditionalAction(std::string _name, std::function<bool()> _condition, std::function<void()> _action);
        // removeConditionalAction(...)
        // *

        // * Flags
        void createFlag(std::string _name);
        bool getFlag(std::string flagName);
        void setFlag(std::string flagName, bool value);        
        // removeflag()
        // *

        void update(float dt);

    private:
        std::map<std::string, std::function<void()>> actions;
        std::map<std::string, ContinuousAction> continuousActions;
        std::map<std::string, ConditionalAction> conditionalActions;
        std::map<std::string, bool> flags;
};

#endif

class PhysicsManager{
    public:
        void registerPhysicalObject(PhysicalObject* _physicalObject);
        void deregisterPhysicalObject(PhysicalObject* _physicalObject);
        std::vector<PhysicalObject*> getAllPhysicalObjects();

        void updatePhysics(float dt);

    private:
        std::vector<PhysicalObject*> physicalObjects;
};

#endif

#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <SFML/Graphics.hpp>
#ifndef COLLISION_PAIR_H
#define COLLISION_PAIR_H

#include <SFML/Graphics.hpp> 
#ifndef COLLISION_H
#define COLLISION_H

#ifndef COLLISION_SIDE_H
#define COLLISION_SIDE_H

enum CollisionSide{ left, right, top, bottom };

#endif
#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include <SFML/Graphics.hpp>
#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H

struct Measurements{
    float x;
    float y;
    float height;
    float width;
};

#endif

class CollisionShape : public sf::RectangleShape{
    public:
        CollisionShape(PhysicalObject *_owner);

        sf::Vector2f offset = sf::Vector2f(0, 0);

        PhysicalObject* getOwner();
        Measurements getMeasurements();
        void align();

    private:
        PhysicalObject *owner;
};

#endif

struct Collision{
    CollisionShape *initiator;
    CollisionShape *recipient;
    CollisionSide initiatorImpactSide;
    CollisionSide recipientImpactSide;
    // ? detectionAlgorithm (string?)
};

#endif

struct CollisionPair{
    std::pair<std::string, std::string> collisionGroups;
    std::vector<std::function<void(std::vector<Collision>)>> collisionResponses;
    std::function<bool(CollisionShape *initiator, CollisionShape *recipient)> checkCollision;
};

#endif

// ? allow to add an 'area' where collisions get calculated 
// ? addToGroup(...), removeFromGroup(...), reloadGroup(...) (checks if pointers are still valid), removePair(...), removeCOllisionResponse(...)
class CollisionManager{
    public:
        void registerCollisionShape(CollisionShape* _collisionShape);
        void deregisterCollisionShape(CollisionShape* _collisionShape);
        void registerCollisionShapes(std::vector<CollisionShape*> _collisionShapes);
        void degisterCollisionShapes(std::vector<CollisionShape*> _collisionShapes);

        void registerCollisionGroup(std::string name, std::vector<CollisionShape*> _collisionGroup);
        void deregisterCollisionGroup(std::string name);
        void registerCollisionGroups(std::map<std::string, std::vector<CollisionShape*>> _groupsToRegister);
        void deregisterCollisionGroups(std::map<std::string, std::vector<CollisionShape*>> _groupsToDeregister);
        
        void createCollisionPair(std::string name, std::string group1, std::string group2);
        void addCollisionResponse(std::string collisionPairName, const std::function<void(std::vector<Collision>)> &response);
        void setCollisionDetectionAlgorithm(std::string collisionPairName, const std::function<bool(CollisionShape* initiator, CollisionShape* recipient)> &cda);

        std::vector<CollisionShape*> getAllCollisionShapes();
        std::map<std::string, std::vector<CollisionShape*>> getCollisionGroups();

        void alignCollisionShapes();
        void updateCollisions();

    private:
        std::vector<CollisionShape*> allCollisionShapes;
        std::map<std::string, std::vector<CollisionShape*>> collisionGroups;
        std::map<std::string, CollisionPair> collisionPairs;
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

    TextureSheetSizes(int textureSizeX_, int textureSizeY_, int numTexturesX_, int numTexturesY_){
        textureSizeX = textureSizeX_;
        textureSizeY = textureSizeY_;
        numTexturesX = numTexturesX_;
        numTexturesY = numTexturesY_;
    }

};

#endif
#ifndef TEXTURESHEET_H
#define TEXTURESHEET_H

#include <SFML/Graphics.hpp>

// TODO texturesheet with gaps between textures
class TextureSheet{
    public:
        TextureSheet(TextureSheetSizes tss, std::string location);

        // TODO make names shorter
        std::string getLocation();
        sf::Texture* getTextureSheet();
        sf::IntRect getTextureRect(int textureN);

    private:
        std::string location;
        sf::Texture textureSheet;
        std::vector<sf::IntRect> textureRects;
};

#endif
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

// TODO Animations should switch immediately
class Animation{
    public:
        Animation(TextureSheet *spritesheet, sf::Sprite *owner, int initialTextureN);
    
        // ?
        // runForward -> 1,2,3,1,2,3
        // runCycle -> 1,2,3,2,1,2
        // ?
        void run();
        
        void restartClock();
        
        void addAnimationSequence(std::string sequenceName, std::vector<int> textureSequence);
        void setCurrentAnimationSequence(std::string sequenceName);

    private:
        sf::Sprite *owner;
        TextureSheet *textureSheet;
        
        sf::Clock clock;
        std::map<std::string, std::vector<int>> animationSequences; // e.g. "idle": [5, 6, 7, 8]
        std::string currentAnimationSequence;
        int currentTextureN = 0;

};

#endif

class TextureManager{
    public:
        // * Textures
        void loadTexture(std::string location, std::string name, TextureSheetSizes textureSheetSizes);
        TextureSheet* getTexture(std::string name); // TODO check nonexistent data (return nullptr?)
        // *

        // * Animations
        void registerAnimation(Animation* animation);
        void deregisterAnimation(Animation* animation);
        // *

        void initAnimationClocks();
        void updateAnimations();

    private:
        std::map<std::string, TextureSheet*> loadedTextures;
        std::vector<Animation*> animations;
};

#endif
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#ifndef ENTITY_H
#define ENTITY_H

struct Entity{
    PhysicalObject* physicalObject;
    std::map<std::string, CollisionShape*> collisionShapes; 
    Animation* animation = nullptr;
};

#endif

class EntityManager{
    public:
        EntityManager(PhysicsManager* _physicsManager, CollisionManager* _collisionManager, TextureManager* _textureManager);

        void registerEntityGroup(std::string name, std::vector<Entity*> _entityGroup);
        std::map<std::string, std::vector<Entity*>> getAllEntityGroups();
        void destroyEntityGroup(std::string name);
        void destroyEntity(std::string memberEntityGroup, Entity* entity);

    private:
        std::map<std::string, std::vector<Entity*>> entityGroups;

        PhysicsManager* physicsManagerPtr;
        CollisionManager* collisionManagerPtr;
        TextureManager* textureManagerPtr;

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
        DebugEntity(Entity* _relatedEntity);

        bool drawCollisionShapeBorders = true;
        std::map<std::string, CollisionShapeBorderSettings> customCollisionShapeBorderSettings;

        std::vector<CollisionShapeBorder*> generateCollisionShapeBorders();

        void addExtraDebugFunction(std::function<void(sf::RenderWindow* windowPtr)> edf);
        std::vector<std::function<void(sf::RenderWindow* windowPtr)>> getExtraDebugFunctions();

    private:
        Entity* relatedEntity;

        CollisionShapeBorderSettings defaultCollisionShapeBorderSettings = CollisionShapeBorderSettings();

        std::vector<std::function<void(sf::RenderWindow* windowPtr)>> extraDebugFunctions;
};

#endif

class DebugManager{
    public:
        void registerDebugEntity(DebugEntity* de);

        void showDebugInfo(sf::RenderWindow* windowPtr);

    private:
        std::vector<DebugEntity*> debugEntities;
};

#endif

class Universe{
    public:
        Universe(PhysicsManager* _physicsManager, CollisionManager* _collisionManager, TextureManager* _textureManager, EntityManager* _entityManager);
        Universe(PhysicsManager* _physicsManager, CollisionManager* _collisionManager, TextureManager* _textureManager, EntityManager* _entityManager, DebugManager* _debugManager);

        void setupWindow(sf::RenderWindow *window);

        void addController(std::function<void()> controller);
        void addEventHandler(std::function<void(sf::Event event)> eventHandler);

        void loop();

        PhysicsManager* physicsManager;
        CollisionManager* collisionManager;
        TextureManager* textureManager;
        EntityManager* entityManager;
        DebugManager* debugManager;

    private:
        sf::RenderWindow *windowPtr;

        sf::Clock deltaClock;
        
        std::vector<std::function<void()>> controllers;
        std::vector<std::function<void(sf::Event event)>> eventHandlers;
};

#endif

#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

void resolveAABB(std::vector<Collision> collisions){
    for(Collision collision : collisions){
        PhysicalObject *initiatorOwner = collision.initiator->getOwner();
        PhysicalObject *recipientOwner = collision.recipient->getOwner();
        
        // Align initiator based on impact side
        if(collision.initiatorImpactSide == CollisionSide::left){
            initiatorOwner->setPosition(
                recipientOwner->getPosition().x + recipientOwner->getGlobalBounds().width - collision.initiator->offset.x,
                initiatorOwner->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == CollisionSide::right){
            initiatorOwner->setPosition(
                recipientOwner->getPosition().x - collision.initiator->getGlobalBounds().width - collision.initiator->offset.x,
                initiatorOwner->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == CollisionSide::top){
            initiatorOwner->setPosition(
                initiatorOwner->getPosition().x,
                recipientOwner->getPosition().y + recipientOwner->getGlobalBounds().height - collision.initiator->offset.y
            );
        }
        else if(collision.initiatorImpactSide == CollisionSide::bottom){
            initiatorOwner->setPosition(
                initiatorOwner->getPosition().x,
                recipientOwner->getPosition().y - collision.initiator->getGlobalBounds().height - collision.initiator->offset.y
            );
        }
    }
}

void initiatorStandOnTopOfRecipient(std::vector<Collision> collisions){
    for(Collision collision : collisions){
        if(collision.initiatorImpactSide == CollisionSide::bottom){
            collision.initiator->getOwner()->velocity.y = 0;
        }
    }
}

#endif
#ifndef COLLISION_DETECTION_ALGORITHMS_H
#define COLLISION_DETECTION_ALGORITHMS_H

bool boundingBox(CollisionShape *initiator, CollisionShape *recipient){
    return initiator->getGlobalBounds().intersects(recipient->getGlobalBounds());
}

// TODO
// bool rayRect(){}

#endif

#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

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

    // ! Order matters 
    if(initiator->getOwner()->velocity.x < 0) allImpactSides.push_back(CollisionSide::left);
    if(initiator->getOwner()->velocity.x > 0) allImpactSides.push_back(CollisionSide::right);
    if(initiator->getOwner()->velocity.y < 0) allImpactSides.push_back(CollisionSide::top);
    if(initiator->getOwner()->velocity.y > 0) allImpactSides.push_back(CollisionSide::bottom);

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

#endif

#ifndef SGE_MAIN

// * Actions
void PhysicalObject::createAction(std::string _name, std::function<void()> _action){ actions[_name] = _action; }

void PhysicalObject::doAction(std::string actionName){
    if(!actions.count(actionName)){
        printf("Action '%s' does not exist\n", actionName.c_str());
        return;
    }

    actions[actionName]();
}

void PhysicalObject::createContinuousAction(std::string _name, std::function<void(float dt)> _action){ continuousActions[_name] = { false, _action }; }
void PhysicalObject::runContinuousAction(std::string continousActionName){ continuousActions[continousActionName].shouldRun = true; }
void PhysicalObject::stopContinuousAction(std::string continousActionName){ continuousActions[continousActionName].shouldRun = false; }

void PhysicalObject::createConditionalAction(std::string _name, std::function<bool()> _condition, std::function<void()> _action){ conditionalActions[_name] = { _condition, _action }; }
// *

// * Flags
// ! check if flags exist before returning
void PhysicalObject::createFlag(std::string _name){ flags[_name] = false; }
bool PhysicalObject::getFlag(std::string flagName){ return flags[flagName]; }
void PhysicalObject::setFlag(std::string flagName, bool value){ flags[flagName] = value; }
//*

void PhysicalObject::update(float dt){
    for(auto const& [name, continuousAction] : continuousActions){
        if(continuousAction.shouldRun) continuousAction.runAction(dt);
    }

    for(auto const& [name, conditionalAction] : conditionalActions){
        if(conditionalAction.condition()){
            conditionalAction.runAction();
        }
    }

    setPosition(getPosition() + velocity * dt);
};


void PhysicsManager::registerPhysicalObject(PhysicalObject* _physicalObject){ physicalObjects.push_back(_physicalObject); }

void PhysicsManager::deregisterPhysicalObject(PhysicalObject* _physicalObject){ physicalObjects.erase(std::remove(physicalObjects.begin(), physicalObjects.end(), _physicalObject), physicalObjects.end()); }

std::vector<PhysicalObject*> PhysicsManager::getAllPhysicalObjects(){ return physicalObjects; }

void PhysicsManager::updatePhysics(float dt){
    for(PhysicalObject* physicalObject : physicalObjects){
        // Accelerate (approach with step)
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
        //

        physicalObject->update(dt);
    }
}


CollisionShape::CollisionShape(PhysicalObject *_owner){
    owner = _owner;

    this->setFillColor(sf::Color(0,0,0,0));
    this->setSize(sf::Vector2f(_owner->getGlobalBounds().width, _owner->getGlobalBounds().height));
}

PhysicalObject* CollisionShape::getOwner(){ return owner; }

Measurements CollisionShape::getMeasurements(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}

void CollisionShape::align(){
    this->setPosition(owner->getPosition() + offset);
}


void CollisionManager::registerCollisionShape(CollisionShape* _collisionShape){ allCollisionShapes.push_back(_collisionShape); }

void CollisionManager::deregisterCollisionShape(CollisionShape* _collisionShape){ allCollisionShapes.erase(std::remove(allCollisionShapes.begin(), allCollisionShapes.end(), _collisionShape), allCollisionShapes.end()); }

void CollisionManager::registerCollisionShapes(std::vector<CollisionShape*> _collisionShapes){ allCollisionShapes.insert(allCollisionShapes.end(), _collisionShapes.begin(), _collisionShapes.end()); }

void CollisionManager::degisterCollisionShapes(std::vector<CollisionShape*> _collisionShapes){
    for(CollisionShape* collisionShape : _collisionShapes){
        deregisterCollisionShape(collisionShape);
    }
}

void CollisionManager::registerCollisionGroup(std::string name, std::vector<CollisionShape*> _collisionGroup){ collisionGroups[name] = _collisionGroup; } 

void CollisionManager::deregisterCollisionGroup(std::string name){ collisionGroups.erase(name); }

void CollisionManager::registerCollisionGroups(std::map<std::string, std::vector<CollisionShape*>> _groupsToRegister){ collisionGroups.insert(_groupsToRegister.begin(), _groupsToRegister.end()); }

void CollisionManager::deregisterCollisionGroups(std::map<std::string, std::vector<CollisionShape*>> _groupsToDeregister){
    for(auto& [name, _] : _groupsToDeregister){
        deregisterCollisionGroup(name);
    }
}

void CollisionManager::createCollisionPair(std::string name, std::string group1, std::string group2){
    // TODO Check if both groups exist in collisionGroups
    collisionPairs[name] = CollisionPair{std::make_pair(group1, group2)};
}

void CollisionManager::addCollisionResponse(std::string collisionPairName, const std::function<void(std::vector<Collision>)> &response){
    collisionPairs[collisionPairName].collisionResponses.push_back(response);
}

void CollisionManager::setCollisionDetectionAlgorithm(std::string collisionPairName, const std::function<bool(CollisionShape *CS1, CollisionShape *CS2)> &cda){
    collisionPairs[collisionPairName].checkCollision = cda;
}

std::vector<CollisionShape*> CollisionManager::getAllCollisionShapes(){ return allCollisionShapes; }

std::map<std::string, std::vector<CollisionShape*>> CollisionManager::getCollisionGroups(){ return collisionGroups; }

void CollisionManager::alignCollisionShapes(){
    for(CollisionShape* collisionShape : allCollisionShapes){
        collisionShape->align();
    }
}

void CollisionManager::updateCollisions(){
    std::vector<Collision> collisions;

    for(auto const& [name, pair] : collisionPairs){
        for(CollisionShape* initiator : collisionGroups[pair.collisionGroups.first]){
            for(CollisionShape* recipient : collisionGroups[pair.collisionGroups.second]){
                if(pair.checkCollision(initiator, recipient)){
                    CollisionSide initiatorImpactSide = determineInitiatorImpactSide(initiator, recipient);

                    collisions.push_back(Collision{
                        initiator,
                        recipient,
                        initiatorImpactSide,
                        flipInitiatorImpactSide(initiatorImpactSide)
                    });
                }
            }

            // Run collision responses
            if(collisions.size()){
                for(std::function collisionResponse : pair.collisionResponses){
                    collisionResponse(collisions);
                }
            }

            // Reset
            collisions.clear();
        }
    }
}


TextureSheet::TextureSheet(TextureSheetSizes tss, std::string location){
    this->location = location;
    textureSheet.loadFromFile(location);

    // Create coordinates vector
    for(int i = 0; i < tss.numTexturesY*tss.textureSizeY; i += tss.textureSizeY){
        for(int j = 0; j < tss.numTexturesX*tss.textureSizeX; j += tss.textureSizeX){
            textureRects.push_back(sf::IntRect(j, i, tss.textureSizeX, tss.textureSizeY));
        }
    }
}

std::string TextureSheet::getLocation(){
    return location;
}

sf::Texture* TextureSheet::getTextureSheet(){
    return &textureSheet;
}

sf::IntRect TextureSheet::getTextureRect(int textureN){
    // TODO check if out of bounds
    return textureRects[textureN];
}


Animation::Animation(TextureSheet *spritesheet, sf::Sprite *owner, int initialTextureN){
    this->textureSheet = spritesheet;
    this->owner = owner;
    
    owner->setTexture(*spritesheet->getTextureSheet());
    owner->setTextureRect(spritesheet->getTextureRect(initialTextureN));
}

void Animation::run(){
    if(!currentAnimationSequence.length()){
        printf("Can not run animation if no currentAnimationSequence is set.\n"); // ? Default to first added ?
        if(animationSequences.size()){
            printf("Available animations:\n");
            for(auto const &pair: animationSequences){
                printf("%s\n", pair.first.c_str());
            }
        }
        else{
            printf("No animation sequences initialized.\n");
        }
        exit(1);
    }

    // TODO dynamic animation delay (for each animation ?)
    if(clock.getElapsedTime().asMilliseconds() > 100){
        owner->setTextureRect(textureSheet->getTextureRect(animationSequences[currentAnimationSequence].at(currentTextureN)));
        
        if(currentTextureN+1 == animationSequences[currentAnimationSequence].size()){
            currentTextureN = 0;
        }
        else currentTextureN++;

        
        clock.restart();
    }
}

void Animation::restartClock(){
    clock.restart();
}

void Animation::addAnimationSequence(std::string sequenceName, std::vector<int> textureSequence){
    // Ensure uniqueness
    if(animationSequences.count(sequenceName)){
        printf("Animation '%s' already exists.\n", sequenceName.c_str());
        return;
    }
    
    animationSequences[sequenceName] = textureSequence;
}

void Animation::setCurrentAnimationSequence(std::string sequenceName){
    if(currentAnimationSequence != sequenceName){
        currentAnimationSequence = sequenceName;
        currentTextureN = 0;
        clock.restart();
    }
}

// * Textures
void TextureManager::loadTexture(std::string location, std::string name, TextureSheetSizes textureSheetSizes){ loadedTextures[name] = new TextureSheet(textureSheetSizes, location); }
TextureSheet* TextureManager::getTexture(std::string name){ return loadedTextures[name]; }
// *

// * Animations
void TextureManager::registerAnimation(Animation* animation){ animations.push_back(animation); }
void TextureManager::deregisterAnimation(Animation* animation){ animations.erase(std::remove(animations.begin(), animations.end(), animation), animations.end()); }
// *

void TextureManager::initAnimationClocks(){
    for(Animation* animation : animations){
        animation->restartClock();
    }
}

void TextureManager::updateAnimations(){
    for(Animation* animation : animations){
        animation->run();
    }
}



EntityManager::EntityManager(PhysicsManager* _physicsManager, CollisionManager* _collisionManager, TextureManager* _textureManager){
    physicsManagerPtr = _physicsManager;
    collisionManagerPtr = _collisionManager;
    textureManagerPtr = _textureManager;
}

void EntityManager::registerEntityGroup(std::string name, std::vector<Entity*> _entityGroup){
    
    for(Entity* entity : _entityGroup){
        physicsManagerPtr->registerPhysicalObject(entity->physicalObject);
        
        // Map to vector
        std::vector<CollisionShape*> entityCollisionShapes;
        for(auto& [_, collisionShape] : entity->collisionShapes){
            entityCollisionShapes.push_back(collisionShape);
        }
        //
        collisionManagerPtr->registerCollisionShapes(entityCollisionShapes);
        
        if(entity->animation){
            textureManagerPtr->registerAnimation(entity->animation);
        }
    }

    entityGroups[name] = _entityGroup;    
}

std::map<std::string, std::vector<Entity*>> EntityManager::getAllEntityGroups(){ return entityGroups; }

// TODO destroy

CollisionShapeBorder::CollisionShapeBorder(CollisionShape* owner, CollisionShapeBorderSettings settings){
    this->setFillColor(sf::Color(0,0,0,0));

    this->setOutlineColor(settings.color);
    this->setOutlineThickness(settings.thickness);

    this->setPosition(sf::Vector2f(owner->getPosition().x + settings.thickness, owner->getPosition().y + settings.thickness));
    this->setSize(sf::Vector2f(owner->getSize().x - settings.thickness*2, owner->getSize().y - settings.thickness*2));
}


DebugEntity::DebugEntity(Entity* _relatedEntity){ relatedEntity = _relatedEntity; }

std::vector<CollisionShapeBorder*> DebugEntity::generateCollisionShapeBorders(){
    std::vector<CollisionShapeBorder*> collisionShapeBorders;

    for(auto &[name, collisionShape] : relatedEntity->collisionShapes){
        if(customCollisionShapeBorderSettings.count(name)){
            collisionShapeBorders.push_back(new CollisionShapeBorder(collisionShape, customCollisionShapeBorderSettings[name]));
        }
        else{
            collisionShapeBorders.push_back(new CollisionShapeBorder(collisionShape, defaultCollisionShapeBorderSettings));
        }
    }

    return collisionShapeBorders;
}

void DebugEntity::addExtraDebugFunction(std::function<void(sf::RenderWindow* windowPtr)> edf){ extraDebugFunctions.push_back(edf); }

std::vector<std::function<void(sf::RenderWindow* windowPtr)>> DebugEntity::getExtraDebugFunctions(){ return extraDebugFunctions; }


void DebugManager::registerDebugEntity(DebugEntity* de){ debugEntities.push_back(de); }

void DebugManager::showDebugInfo(sf::RenderWindow* windowPtr){
    for(DebugEntity* debugEntity : debugEntities){
        // Run extraDebugFunctions
        for(std::function<void(sf::RenderWindow* rw)> edf : debugEntity->getExtraDebugFunctions()){
            edf(windowPtr);
        }

        // Collision shape borders
        if(debugEntity->drawCollisionShapeBorders){
            for(CollisionShapeBorder* csb : debugEntity->generateCollisionShapeBorders()){
                windowPtr->draw(*csb);
            }
        }
    }
}


Universe::Universe(PhysicsManager* _physicsManager, CollisionManager* _collisionManager, TextureManager* _textureManager, EntityManager* _entityManager){
    physicsManager = _physicsManager;
    collisionManager = _collisionManager;
    textureManager = _textureManager;
    entityManager = _entityManager;
}

Universe::Universe(PhysicsManager* _physicsManager, CollisionManager* _collisionManager, TextureManager* _textureManager, EntityManager* _entityManager, DebugManager* _debugManager){
    physicsManager = _physicsManager;
    collisionManager = _collisionManager;
    textureManager = _textureManager;
    entityManager = _entityManager;
    debugManager = _debugManager;
}

void Universe::setupWindow(sf::RenderWindow *window){
    windowPtr = window;
}

void Universe::addController(std::function<void()> controller){
    controllers.push_back(controller);
}

void Universe::addEventHandler(std::function<void(sf::Event event)> eventHandler){
    eventHandlers.push_back(eventHandler);
}

void Universe::loop(){
    if(!windowPtr){
        printf("RenderWindow is not initialized. Use setupWindow method to initialize RenderWindow before(!) looping the Universe.\n");
        exit(1);
    }

    // Clocks initialization
    // ! Remove in the future (init on animation creation?)
    textureManager->initAnimationClocks();
    // !

    deltaClock.restart();
    //

    while(windowPtr->isOpen()){
        sf::Event event;
        while(windowPtr->pollEvent(event)){
            if (event.type == sf::Event::Closed) windowPtr->close();
        
            for(std::function eventHandler : eventHandlers){
                eventHandler(event);
            }
        }

        // Controllers
        for(std::function controller : controllers){
            controller();
        }

        windowPtr->clear();

        // Calculate dt
        sf::Time deltaTime = deltaClock.restart();
        float dt = deltaTime.asSeconds();
        if(dt > 0.15f) dt = 0.15f;
        //

        // Game updates
        physicsManager->updatePhysics(dt);
        collisionManager->alignCollisionShapes();
        collisionManager->updateCollisions();
        textureManager->updateAnimations();
        // 

        // Game draws
        for(PhysicalObject* physicalObject : physicsManager->getAllPhysicalObjects()){
            windowPtr->draw(*physicalObject);
        }

        // for(CollisionShape* collisionShape : collisionManager->getAllCollisionShapes()){
        //     if(collisionShape->getIsVisible()) windowPtr->draw(*collisionShape->getBorder());
        // }

        if(debugManager){
            debugManager->showDebugInfo(windowPtr);
        }

        windowPtr->display();
    }
}


#endif