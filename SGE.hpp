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

#ifndef COLLISION_GROUP_H
#define COLLISION_GROUP_H

#include <SFML/Graphics.hpp>
#ifndef COLLISION_GROUP_TYPE
#define COLLISION_GROUP_TYPE

enum CollisionGroupType{ solid, moveable };

#endif
#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include <SFML/Graphics.hpp>
#ifndef COLLISION_SHAPE_POSITION_DATA_H
#define COLLISION_SHAPE_POSITION_DATA_H

struct CollisionShapePositionData{
    float x;
    float y;
    float height;
    float width;
};

#endif

class CollisionShape : public sf::RectangleShape{
    public:
        CollisionShape(PhysicalObject *_owner);

        PhysicalObject* getOwner();

        CollisionShapePositionData getPositionData();

        sf::Vector2f getOffset();
        void setOffset(sf::Vector2f _offset);

        void setSize(const sf::Vector2f& size);

        // Border
        bool getIsVisible();
        void setIsVisible(bool is);

        sf::RectangleShape* getBorder();
        void setBorderThickness(float thickness);
        void setBorderColor(const sf::Color& color);
        //

        void align();

    private:
        PhysicalObject *owner;

        sf::Vector2f offset = sf::Vector2f(0, 0);

        bool isVisible = true;
        sf::RectangleShape border;
};

#endif
#ifndef ENTITY_H
#define ENTITY_H

#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#ifndef TEXTURESHEET_H
#define TEXTURESHEET_H

#include <SFML/Graphics.hpp>
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

struct Entity{
    PhysicalObject* physicalObject;
    std::map<std::string, CollisionShape*> collisionShapes; 
    Animation* animation = nullptr;
};

#endif

struct CollisionGroup{
    CollisionGroupType collisionGroupType;
    std::vector<CollisionShape*> collisionShapes;
    std::vector<Entity*> ownerEntities;
};

#endif

#ifndef COLLISION_PAIR_H
#define COLLISION_PAIR_H

#include <SFML/Graphics.hpp> 
#ifndef COLLISION_H
#define COLLISION_H

#ifndef COLLISION_SIDE_H
#define COLLISION_SIDE_H

enum CollisionSide{ left, right, top, bottom };

#endif

struct Collision{
    CollisionSide side;
    CollisionShape *from;
    CollisionShape *with;
    // ? detectionAlgorithm (string?)
};

#endif

// ? add collision type specifier (rectangle, circle etc.)
struct CollisionPair{
    std::tuple<std::string, std::string> collisionGroups;
    std::vector<std::function<void(std::vector<Collision>)>> collisionResponses; // TODO allow function with and without parameters (struct || simply register different types of functions and use the one that exists (or all of them))
    std::function<bool(CollisionShape *CS1, CollisionShape *CS2)> checkCollision;
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

        void registerCollisionGroup(std::string name, CollisionGroup* _collisionGroup);
        void deregisterCollisionGroup(std::string name);
        void registerCollisionGroups(std::map<std::string, CollisionGroup*> _groupsToRegister);
        void deregisterCollisionGroups(std::map<std::string, CollisionGroup*> _groupsToDeregister);
        
        void createCollisionPair(std::string name, std::string group1, std::string group2);
        void addCollisionResponse(std::string collisionPairName, const std::function<void(std::vector<Collision>)> &response);
        void setCollisionDetectionAlgorithm(std::string collisionPairName, const std::function<bool(CollisionShape *CS1, CollisionShape *CS2)> &cda);

        std::vector<CollisionShape*> getAllCollisionShapes();
        std::map<std::string, CollisionGroup*> getCollisionGroups();

        void alignCollisionShapes();
        void updateCollisions();

    private:
        std::vector<CollisionShape*> allCollisionShapes;
        std::map<std::string, CollisionGroup*> collisionGroups;
        std::map<std::string, CollisionPair> collisionPairs;
};

#endif
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

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

class Universe{
    public:
        Universe(PhysicsManager* _physicsManager, CollisionManager* _collisionManager, TextureManager* _textureManager, EntityManager* _entityManager);

        void setupWindow(sf::RenderWindow *window);

        void addController(std::function<void()> controller);
        void addEventHandler(std::function<void(sf::Event event)> eventHandler);

        void loop();

        PhysicsManager* physicsManager;
        CollisionManager* collisionManager;
        TextureManager* textureManager;
        EntityManager* entityManager;

    private:
        sf::RenderWindow *windowPtr;

        sf::Clock deltaClock;
        
        std::vector<std::function<void()>> controllers;
        std::vector<std::function<void(sf::Event event)>> eventHandlers;
};

#endif

#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

#include <limits>

float determineCollisionDepth(CollisionSide side, CollisionShape *CS1, CollisionShape *CS2){
    auto [x1, y1, height1, width1] = CS1->getPositionData();
    auto [x2, y2, height2, width2] = CS2->getPositionData();
    
    if(side == CollisionSide::left) return x2 + width2 - x1;
    if(side == CollisionSide::right) return x1 + width1 - x2;
    if(side == CollisionSide::top) return y2 + height2 - y1;
    if(side == CollisionSide::bottom) return y1 + height1 - y2;

    return 0;
}

CollisionSide determineCollisionSide(CollisionShape *CS1, CollisionShape *CS2){
    std::vector<CollisionSide> allCollisionSides;

    // ! Order matters 
    if(CS1->getOwner()->velocity.x < 0) allCollisionSides.push_back(CollisionSide::left);
    if(CS1->getOwner()->velocity.x > 0) allCollisionSides.push_back(CollisionSide::right);
    if(CS1->getOwner()->velocity.y < 0) allCollisionSides.push_back(CollisionSide::top);
    if(CS1->getOwner()->velocity.y > 0) allCollisionSides.push_back(CollisionSide::bottom);

    CollisionSide lowestDepthSide;
    float lowestDepth = std::numeric_limits<float>::infinity();
    
    for(CollisionSide collisionSide : allCollisionSides){
        float depth = determineCollisionDepth(collisionSide, CS1, CS2);
        if(depth <= lowestDepth){
            lowestDepthSide = collisionSide;
            lowestDepth = depth;
        }
    }

    return lowestDepthSide;
}

#endif

void resolveAABB(std::vector<Collision> collisions){
    for(Collision collision : collisions){
        PhysicalObject *fromOwner = collision.from->getOwner();
        PhysicalObject *withOwner = collision.with->getOwner();
        
        if(collision.side == CollisionSide::left){
            fromOwner->setPosition(
                withOwner->getPosition().x + withOwner->getGlobalBounds().width - collision.from->getOffset().x,
                fromOwner->getPosition().y
            );
        }
        else if(collision.side == CollisionSide::right){
            fromOwner->setPosition(
                withOwner->getPosition().x - collision.from->getGlobalBounds().width - collision.from->getOffset().x,
                fromOwner->getPosition().y
            );
        }
        else if(collision.side == CollisionSide::top){
            fromOwner->setPosition(
                fromOwner->getPosition().x,
                withOwner->getPosition().y + withOwner->getGlobalBounds().height - collision.from->getOffset().y
            );
        }
        else if(collision.side == CollisionSide::bottom){
            fromOwner->setPosition(
                fromOwner->getPosition().x,
                withOwner->getPosition().y - collision.from->getGlobalBounds().height - collision.from->getOffset().y
            );
        }
    }
}

#endif
#ifndef COLLISION_DETECTION_ALGORITHMS_H
#define COLLISION_DETECTION_ALGORITHMS_H

bool boundingBox(CollisionShape *CS1, CollisionShape *CS2){
    return CS1->getGlobalBounds().intersects(CS2->getGlobalBounds());
}

// TODO
// bool rayRect(){}

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
    
    this->border.setFillColor(sf::Color(0,0,0,0));
    setBorderColor(sf::Color::Blue);
    setBorderThickness(.5);
}

PhysicalObject* CollisionShape::getOwner(){ return owner; }

CollisionShapePositionData CollisionShape::getPositionData(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}

sf::Vector2f CollisionShape::getOffset(){ return offset; }
void CollisionShape::setOffset(sf::Vector2f _offset){ offset = _offset; }

void CollisionShape::setSize(const sf::Vector2f& size){
    this->RectangleShape::setSize(size);
    border.setSize(sf::Vector2f(size.x-border.getOutlineThickness()*2, size.y-border.getOutlineThickness()*2));
}

// Border
bool CollisionShape::getIsVisible(){ return isVisible; }
void CollisionShape::setIsVisible(bool is){ isVisible = is; }

sf::RectangleShape* CollisionShape::getBorder(){ return &border; }
void CollisionShape::setBorderThickness(float thickness){
    border.setSize(sf::Vector2f(this->getSize().x-thickness*2, this->getSize().y-thickness*2));
    border.setOutlineThickness(thickness);
}
void CollisionShape::setBorderColor(const sf::Color& color){ border.setOutlineColor(color); }
//

void CollisionShape::align(){
    this->setPosition(owner->getPosition() + offset);
    border.setPosition(sf::Vector2f(this->getPosition().x+border.getOutlineThickness(), this->getPosition().y+border.getOutlineThickness()));
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

void CollisionManager::registerCollisionShape(CollisionShape* _collisionShape){ allCollisionShapes.push_back(_collisionShape); }

void CollisionManager::deregisterCollisionShape(CollisionShape* _collisionShape){ allCollisionShapes.erase(std::remove(allCollisionShapes.begin(), allCollisionShapes.end(), _collisionShape), allCollisionShapes.end()); }

void CollisionManager::registerCollisionShapes(std::vector<CollisionShape*> _collisionShapes){ allCollisionShapes.insert(allCollisionShapes.end(), _collisionShapes.begin(), _collisionShapes.end()); }

void CollisionManager::degisterCollisionShapes(std::vector<CollisionShape*> _collisionShapes){
    for(CollisionShape* collisionShape : _collisionShapes){
        deregisterCollisionShape(collisionShape);
    }
}

void CollisionManager::registerCollisionGroup(std::string name, CollisionGroup* _collisionGroup){ collisionGroups[name] = _collisionGroup; } 

void CollisionManager::deregisterCollisionGroup(std::string name){ collisionGroups.erase(name); }

void CollisionManager::registerCollisionGroups(std::map<std::string, CollisionGroup*> _groupsToRegister){ collisionGroups.insert(_groupsToRegister.begin(), _groupsToRegister.end()); }

void CollisionManager::deregisterCollisionGroups(std::map<std::string, CollisionGroup*> _groupsToDeregister){
    for(auto& [name, _] : _groupsToDeregister){
        deregisterCollisionGroup(name);
    }
}

void CollisionManager::createCollisionPair(std::string name, std::string group1, std::string group2){
    // TODO Check if both groups exist in collisionGroups
    collisionPairs[name] = CollisionPair{std::make_tuple(group1, group2)};
}

void CollisionManager::addCollisionResponse(std::string collisionPairName, const std::function<void(std::vector<Collision>)> &response){
    collisionPairs[collisionPairName].collisionResponses.push_back(response);
}

void CollisionManager::setCollisionDetectionAlgorithm(std::string collisionPairName, const std::function<bool(CollisionShape *CS1, CollisionShape *CS2)> &cda){
    collisionPairs[collisionPairName].checkCollision = cda;
}

std::vector<CollisionShape*> CollisionManager::getAllCollisionShapes(){ return allCollisionShapes; }

std::map<std::string, CollisionGroup*> CollisionManager::getCollisionGroups(){ return collisionGroups; }

void CollisionManager::alignCollisionShapes(){
    for(CollisionShape* collisionShape : allCollisionShapes){
        collisionShape->align();
    }
}

void CollisionManager::updateCollisions(){
    // TODO check if any collision pairs are added

    std::vector<Collision> collisions;

    // TODO refactor ?
    for(auto const& [name, pair] : collisionPairs){
        for(CollisionShape* collisionShape_Group1 : collisionGroups[std::get<0>(pair.collisionGroups)]->collisionShapes){
            for(CollisionShape* collisionShape_Group2 : collisionGroups[std::get<1>(pair.collisionGroups)]->collisionShapes){
                if(pair.checkCollision(collisionShape_Group1, collisionShape_Group2)){
                    Collision collision;
                    collision.side = determineCollisionSide(collisionShape_Group1, collisionShape_Group2);
                    collision.from = collisionShape_Group1; // ! Assuming CS1 is always 'from' (moveable)
                    collision.with = collisionShape_Group2;

                    collisions.push_back(collision);
                }
            }

            // Run responses
            // TODO check if any collisionResponses exist (print message?)
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

Universe::Universe(PhysicsManager* _physicsManager, CollisionManager* _collisionManager, TextureManager* _textureManager, EntityManager* _entityManager){
    physicsManager = _physicsManager;
    collisionManager = _collisionManager;
    textureManager = _textureManager;
    entityManager = _entityManager;
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

        for(CollisionShape* collisionShape : collisionManager->getAllCollisionShapes()){
            if(collisionShape->getIsVisible()) windowPtr->draw(*collisionShape->getBorder());
        }

        windowPtr->display();
    }
}


#endif