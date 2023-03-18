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
#ifndef PHYSICAL_OBJECT_POSITION_DATA_H
#define PHYSICAL_OBJECT_POSITION_DATA_H

struct PhysicalObjectPositionData{
    float x;
    float y;
    float height;
    float width;
};

#endif
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
        // * Utils
        PhysicalObjectPositionData getPositionData();
        // *

        // * Movement
        void setMovementVector(sf::Vector2f _movementVector); // ? Use movement methods in the future?
        void setMovementVectorX(float x); // ? Use movement methods in the future?
        void setMovementVectorY(float y); // ? Use movement methods in the future?
        sf::Vector2f getMovementVector();

        void setVelocityGoal(sf::Vector2f goal);
        void setVelocityGoalX(float goalX);
        void setVelocityGoalY(float goalY);
        
        void movementStop();
        void movementStopX();
        void movementStopY();
        // void movementAccelerate();
        // void movementSlacken();
        // ? void setVelocityCap(...) (sets max possible velocity vector values)
        // ? setMovementFunction(lambda) (sets movement algorithm (e.g. acceleration -> keeping velocity -> slowing down -> stop))
        // *

        // * Actions
        void createAction(std::string _name, std::function<void()> _action);
        void doAction(std::string actionName);

        void createContinuousAction(std::string _name, std::function<void(float dt)> _action);
        void runContinuousAction(std::string continuousActonName);
        void stopContinuousAction(std::string continuousActonName);
        
        void createConditionalAction(std::string _name, std::function<bool()> _condition, std::function<void()> _action);
        // removeConditionalAction(...)
        // *

        // * Physical properties
        void setMass(float _mass);
        float getMass();
        
        void setIsFlying(bool is); // ? Use just mass = 0 to 'fly' ?
        bool getIsFlying();
        // *
        

        void update(float dt);

    private:
        sf::Vector2f movementVector = sf::Vector2f(0, 0);
        sf::Vector2f velocityGoal;

        std::map<std::string, std::function<void()>> actions;
        std::map<std::string, ContinuousAction> continuousActions;
        std::map<std::string, ConditionalAction> conditionalActions;
        
        float mass = 0;
        bool isFlying = false;
};

#endif

class PhysicsManager{
    public:
        void addPhysicalObject(PhysicalObject *physicalObject);
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

struct CollisionGroup{
    CollisionGroupType collisionGroupType;
    std::vector<PhysicalObject*> physicalObjects;
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
    PhysicalObject *from;
    PhysicalObject *with;
    // ? detectionAlgorithm (string?)
};

#endif

// ? add collision type specifier (rectangle, circle etc.)
struct CollisionPair{
    std::tuple<std::string, std::string> collisionGroups;
    std::vector<std::function<void(std::vector<Collision>)>> collisionResponses; // TODO allow function with and without parameters (struct || simply register different types of functions and use the one that exists (or all of them))
    std::function<bool(PhysicalObject *PO1, PhysicalObject *PO2)> checkCollision;
};

#endif

// ? allow to add an 'area' where collisions get calculated 
// ? addToGroup(...), removeFromGroup(...), reloadGroup(...) (checks if pointers are still valid), removePair(...), removeCOllisionResponse(...)
class CollisionManager{
    public:
    void createCollisionGroup(std::string name, CollisionGroupType type, std::vector<PhysicalObject*> physicalObjectsVec); // TODO Overload 3rd argument with sf::Sprite *sprite (and automatically create a vector)
    void createCollisionPair(std::string name, std::string group1, std::string group2);
    void addCollisionResponse(std::string collisionPairName, const std::function<void(std::vector<Collision>)> &response);
    void setCollisionDetectionAlgorithm(std::string collisionPairName, const std::function<bool(PhysicalObject *PO1, PhysicalObject *PO2)> &cda);

    void updateCollisions();

    private:
    std::map<std::string, CollisionGroup> collisionGroups;
    std::map<std::string, CollisionPair> collisionPairs;
};

#endif
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
        void setCurrentAnimationSequence(std::string sequenceName);
        void addAnimationSequence(std::string sequenceName, std::vector<int> textureSequence);

    private:
        sf::Sprite *owner;
        TextureSheet *textureSheet;
        
        sf::Clock clock;
        std::map<std::string, std::vector<int>> animationSequences; // e.g. "idle": [5, 6, 7, 8]
        std::string currentAnimationSequence;
        int currentTextureN = 0;

};

#endif

class Universe{
    public:
        void setupWindow(sf::RenderWindow *window);
        void createPlayer(sf::Sprite *player);
        void addMap(std::vector<PhysicalObject*> *map); // TODO managed in Scene in the future(?)
        void addController(std::function<void()> controller);
        void addEventHandler(std::function<void(sf::Event event)> eventHandler);
        void addAnimation(Animation *animation);

        void loop();

        PhysicsManager physicsManager;
        CollisionManager collisionManager;

    private:
        sf::Clock deltaClock;
        sf::RenderWindow *windowPtr;
        sf::Sprite *playerPtr; // ! for drawing
        std::vector<PhysicalObject*> *mapPtr; // ! for drawing
        std::vector<std::function<void()>> controllers;
        std::vector<std::function<void(sf::Event event)>> eventHandlers;
        std::vector<Animation*> animations;
};

#endif

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

class TextureManager{
    public:
        void load(std::string textureLocation, TextureSheetSizes textureSheetSizes, std::string textureName);
        TextureSheet* get(std::string textureName); // TODO check nonexistent data (return nullptr?)
        // ? not needed
        TextureSheet* getByLocation(std::string textureLocation); // can be used to check whether texture at location has been loaded

    private:
        std::map<std::string, TextureSheet*> loadedTextures;
};

#endif

#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

void resolveAABB(std::vector<Collision> collisions){
    for(Collision collision : collisions){
        PhysicalObject *from = collision.from;
        PhysicalObject *with = collision.with;
        
        if(collision.side == CollisionSide::left){
            from->setPosition(with->getPosition().x + with->getGlobalBounds().width, from->getPosition().y);
        }
        else if(collision.side == CollisionSide::right){
            from->setPosition(with->getPosition().x - from->getGlobalBounds().width, from->getPosition().y);
        }
        else if(collision.side == CollisionSide::top){
            from->setPosition(from->getPosition().x, with->getPosition().y + with->getGlobalBounds().height);
        }
        else if(collision.side == CollisionSide::bottom){
            from->setPosition(from->getPosition().x, with->getPosition().y - from->getGlobalBounds().height);
        }
    }
}

#endif
#ifndef COLLISION_DETECTION_ALGORITHMS_H
#define COLLISION_DETECTION_ALGORITHMS_H

bool boundingBox(PhysicalObject *PO1, PhysicalObject *PO2){
    return PO1->getGlobalBounds().intersects(PO2->getGlobalBounds());
}

// TODO
// bool rayRect(){}

#endif

#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

#include <limits>

float determineCollisionDepth(CollisionSide side, PhysicalObject *PO1, PhysicalObject *PO2){
    auto [x1, y1, height1, width1] = PO1->getPositionData();
    auto [x2, y2, height2, width2] = PO2->getPositionData();
    
    if(side == CollisionSide::left) return x2 + width2 - x1;
    if(side == CollisionSide::right) return x1 + width1 - x2;
    if(side == CollisionSide::top) return y2 + height2 - y1;
    if(side == CollisionSide::bottom) return y1 + height1 - y2;

    return 0;
}

CollisionSide determineCollisionSide(PhysicalObject *PO1, PhysicalObject *PO2){
    std::vector<CollisionSide> allCollisionSides;

    // ! Order matters 
    if(PO1->getMovementVector().x < 0) allCollisionSides.push_back(CollisionSide::left);
    if(PO1->getMovementVector().x > 0) allCollisionSides.push_back(CollisionSide::right);
    if(PO1->getMovementVector().y < 0) allCollisionSides.push_back(CollisionSide::top);
    if(PO1->getMovementVector().y > 0) allCollisionSides.push_back(CollisionSide::bottom);

    CollisionSide lowestDepthSide;
    float lowestDepth = std::numeric_limits<float>::infinity();
    
    for(CollisionSide collisionSide : allCollisionSides){
        float depth = determineCollisionDepth(collisionSide, PO1, PO2);
        if(depth <= lowestDepth){
            lowestDepthSide = collisionSide;
            lowestDepth = depth;
        }
    }

    return lowestDepthSide;
}

#endif

#endif

#ifndef SGE_MAIN

#ifndef APPROACH_H
#define APPROACH_H

float approach(float goal, float current, float dt){
    float diff = goal - current;

    if(diff > dt) return current + dt;
    if(diff < -dt) return current - dt;
    return goal;
}

#endif

// * Utils
PhysicalObjectPositionData PhysicalObject::getPositionData(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}
// *

// * Movement
void PhysicalObject::setMovementVector(sf::Vector2f _movementVector){ movementVector = _movementVector; }
void PhysicalObject::setMovementVectorX(float x){ movementVector = sf::Vector2f(x, movementVector.y); }
void PhysicalObject::setMovementVectorY(float y){ movementVector = sf::Vector2f(movementVector.x, y); }
sf::Vector2f PhysicalObject::getMovementVector(){ return movementVector; }

void PhysicalObject::setVelocityGoal(sf::Vector2f goal){ velocityGoal = goal; }
void PhysicalObject::setVelocityGoalX(float goalX){ velocityGoal.x = goalX; }
void PhysicalObject::setVelocityGoalY(float goalY){ velocityGoal.y = goalY; }

void PhysicalObject::movementStop(){ movementVector = sf::Vector2f(0, 0);  };
void PhysicalObject::movementStopX(){ movementVector = sf::Vector2f(0, movementVector.y); };
void PhysicalObject::movementStopY(){ movementVector = sf::Vector2f(movementVector.x, 0); };
// *

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

// * Physical properties
void PhysicalObject::setMass(float _mass){ mass = _mass; }
float PhysicalObject::getMass(){ return mass; }

void PhysicalObject::setIsFlying(bool is){ isFlying = is; }
bool PhysicalObject::getIsFlying(){ return isFlying ;}
// *

void PhysicalObject::update(float dt){
    // ? Movement is a ContinuousAction ? 
    movementVector.x = approach(velocityGoal.x, movementVector.x, dt*5000);
    movementVector.y = approach(velocityGoal.y, movementVector.y, dt*5000);
    setPosition(getPosition() + movementVector * dt);

    for(auto const& [name, continuousAction] : continuousActions){
        if(continuousAction.shouldRun) continuousAction.runAction(dt);
    }

    for(auto const& [name, conditionalAction] : conditionalActions){
        if(conditionalAction.condition()){
            conditionalAction.runAction();
        }
    }
};


void PhysicsManager::addPhysicalObject(PhysicalObject *physicalObject){
    physicalObjects.push_back(physicalObject);
}

void PhysicsManager::updatePhysics(float dt){
    // TODO check if any physical objects exist
    for(PhysicalObject *pObject : physicalObjects){
        // * Gravity
        if(!pObject->getIsFlying()){
            pObject->setVelocityGoalY(pObject->getMass()); // ?
        }
        // *

        pObject->update(dt);
    }
}


void CollisionManager::createCollisionGroup(std::string name, CollisionGroupType type, std::vector<PhysicalObject*> physicalObjectVec){
    // TODO check if already exists (has length)
    collisionGroups[name] = CollisionGroup {type, physicalObjectVec};
}

void CollisionManager::createCollisionPair(std::string name, std::string group1, std::string group2){
    // TODO Check if both groups exist in collisionGroups
    collisionPairs[name] = CollisionPair{std::make_tuple(group1, group2)};
}

void CollisionManager::addCollisionResponse(std::string collisionPairName, const std::function<void(std::vector<Collision>)> &response){
    collisionPairs[collisionPairName].collisionResponses.push_back(response);
}

void CollisionManager::setCollisionDetectionAlgorithm(std::string collisionPairName, const std::function<bool(PhysicalObject *PO1, PhysicalObject *PO2)> &cda){
    collisionPairs[collisionPairName].checkCollision = cda;
}

void CollisionManager::updateCollisions(){
    // TODO check if any collision pairs are added

    std::vector<Collision> collisions;

    // TODO refactor ?
    for(auto const& [name, pair] : collisionPairs){
        // Determine all collisions
        for(PhysicalObject *physicalObjectCG1 : collisionGroups[std::get<0>(pair.collisionGroups)].physicalObjects){
            for(PhysicalObject *physicalObjectCG2 : collisionGroups[std::get<1>(pair.collisionGroups)].physicalObjects){
                if(pair.checkCollision(physicalObjectCG1, physicalObjectCG2)){
                    Collision collision;
                    collision.side = determineCollisionSide(physicalObjectCG1, physicalObjectCG2);
                    collision.from = physicalObjectCG1; // ! Assuming PO1 is always 'from' (moveable)
                    collision.with = physicalObjectCG2;

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

void Animation::setCurrentAnimationSequence(std::string sequenceName){
    if(currentAnimationSequence != sequenceName){
        currentAnimationSequence = sequenceName;
        currentTextureN = 0;
        clock.restart();
    }
}

void Animation::addAnimationSequence(std::string sequenceName, std::vector<int> textureSequence){
    // Ensure uniqueness
    if(animationSequences.count(sequenceName)){
        printf("Animation '%s' already exists.\n", sequenceName.c_str());
        return;
    }
    
    animationSequences[sequenceName] = textureSequence;
}
#include <iostream>

void Universe::addMap(std::vector<PhysicalObject*> *map){
    mapPtr = map;
}

void Universe::createPlayer(sf::Sprite *player){
    playerPtr = player;
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

void Universe::addAnimation(Animation *animation){
    animations.push_back(animation);
}

void Universe::loop(){
    if(!windowPtr){
        printf("RenderWindow is not initialized. Use setupWindow method to initialize RenderWindow before(!) looping the Universe.\n");
        exit(1);
    }

    // Clocks initialization
    if(!animations.empty()){
        for(Animation *animation : animations){
            animation->restartClock();
        }
    }

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
        physicsManager.updatePhysics(dt);
        collisionManager.updateCollisions();

        if(!animations.empty()){
            for(Animation *animation : animations){
                animation->run();
            }
        }
        // 

        // Game draws
        for(sf::Sprite *tileSprite : *mapPtr){
            windowPtr->draw(*tileSprite);
        }
        
        if(playerPtr){
            windowPtr->draw(*playerPtr);
        }
        // 

        windowPtr->display();
    }
}


void TextureManager::load(std::string textureLocation, TextureSheetSizes textureSheetSizes, std::string textureName){
    if(loadedTextures.count(textureName)){
        printf("Can't load already existing texture '%s'\n", textureName.c_str());
        exit(1);
    }

    loadedTextures[textureName] = new TextureSheet(textureSheetSizes, textureLocation);
}

TextureSheet* TextureManager::get(std::string textureName){
    return loadedTextures[textureName];
}

TextureSheet* TextureManager::getByLocation(std::string textureLocation){
    for(auto &[key, textureSheet] : loadedTextures){
        if(textureSheet->getLocation() == textureLocation) return textureSheet;
    }

    return nullptr;
}


#endif