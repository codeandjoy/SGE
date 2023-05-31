#ifndef SGE_HPP
#define SGE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

namespace sge{
    class AssetsManager;
    class ControllerManager;
    class ScriptedViewManager;
    class DebugManager;

    class SpriteManager;
    class PhysicsManager;
    class CollisionShapeManager;
    class ClickableShapeManager;
    class SpriteTextManager;
    class AnimationManager;
    class CollisionManager;
    class EntityManager;
    class SceneManager;
    

    class Universe{
        public:
            Universe(sf::RenderWindow* window);

            bool isPaused = false;

            void setupDebug();
            void loop();

            sge::AssetsManager* assetsManager = nullptr;
            sge::ControllerManager* controllerManager = nullptr;
            sge::DebugManager* debugManager = nullptr;
            sge::ScriptedViewManager* scriptedViewManager = nullptr;

            sge::CollisionManager* collisionManager = nullptr;
            sge::EntityManager* entityManager = nullptr;
            sge::SceneManager* sceneManager = nullptr;

        private:
            sf::RenderWindow* m_windowPtr;

            sf::Clock m_deltaClock;

            sge::SpriteManager* m_spriteManager = nullptr;
            sge::PhysicsManager* m_physicsManager = nullptr;
            sge::CollisionShapeManager* m_collisionShapeManager = nullptr;
            sge::AnimationManager* m_animationManager = nullptr;

            sge::ClickableShapeManager* m_clickableShapeManager = nullptr;
            sge::SpriteTextManager* m_spriteTextManager = nullptr;
    };
}

#endif

// AssetsManager
#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include <unordered_map>
#include <string>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef TEXTURE_SHEET_SIZES_H
#define TEXTURE_SHEET_SIZES_H

namespace sge{
    struct TextureSheetSizes{
        int textureSizeX;
        int textureSizeY;
        int numTexturesX;
        int numTexturesY;
        int gapX = 0;
        int gapY = 0;
    };
}

#endif

namespace sge{
    class TextureSheet;

    class AssetsManager{
        public:
            void loadTextureSheet(std::string location, std::string name, sge::TextureSheetSizes textureSheetSizes);
            sge::TextureSheet* getTextureSheet(std::string name);

            void loadFont(std::string location, std::string name);
            sf::Font* getFont(std::string name);

            void loadSFX(std::string location, std::string name);
            sf::Sound* getSound(std::string name);

            void specifyMusicLocation(std::string location, std::string name);
            std::string getMusicLocation(std::string name);

        private:
            std::unordered_map<std::string, sge::TextureSheet*> m_textures;
            std::unordered_map<std::string, sf::Font*> m_fonts;
            std::unordered_map<std::string, std::pair<sf::SoundBuffer*, sf::Sound*>> m_sfx;
            std::unordered_map<std::string, std::string> m_musicLocations;
    };
}

#endif

#ifndef TEXTURESHEET_H
#define TEXTURESHEET_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace sge{
    // TODO texturesheet with gaps between textures
    class TextureSheet{
        public:
            TextureSheet(sge::TextureSheetSizes textureSheetSizes, std::string location);

            std::string getLocation();
            sf::Texture* getTexture();
            sf::IntRect getTextureRect(int textureN);

        private:
            std::string m_location;
            sf::Texture m_textureSheet;
            std::vector<sf::IntRect> m_textureRects;
    };
}

#endif
//

// Common

//

// Debug
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
#include <unordered_map>
#include <vector>

namespace sge{
    class DebugEntity;

    class DebugManager{
        public:
            void registerDebugEntity(sf::View* view, sge::DebugEntity* debugEntity);
            void registerDebugEntities(sf::View* view, std::vector<sge::DebugEntity*> debugEntities);
            void deregisterDebugEntity(sf::View* view, sge::DebugEntity* debugEntity);
            void deregisterAllDebugEntities();

            void showDebugInfo(sf::RenderWindow* windowPtr);

        private:
            std::unordered_map<sf::View*, std::vector<sge::DebugEntity*>> m_debugEntities;
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

//

// Controller
#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>

namespace sge{
    class ControllerManager{
        public:
            void registerController(std::function<void(sf::Event)> controller);
            std::vector<std::function<void(sf::Event)>> getAllControllers();       

            void updateControllers(sf::Event event);
            
        private:
            std::vector<std::function<void(sf::Event)>> m_controllers;
    };
}

#endif
//

// View
#ifndef SCRIPTED_VIEW_H
#define SCRIPTED_VIEW_H

#include <functional>
#include <SFML/Graphics.hpp>

namespace sge{
    struct ScriptedView : public sf::View{
        std::function<void(sge::ScriptedView*)> script;
    };
}

#endif
#ifndef SCRIPTED_VIEW_MANAGER_H
#define SCRIPTED_VIEW_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace sge{
    struct ScriptedView;

    class ScriptedViewManager{
        public:
            void registerScriptedView(sge::ScriptedView* scriptedView);

            void runViewScripts();

        private:
            std::vector<sge::ScriptedView*> m_scriptedViews;
    };
}

#endif
//

// Logic
#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

namespace sge{
    class SpriteManager{
        public:
            void registerSprite(sf::View*, sf::Sprite* sprite);
            void deregisterSprite(sf::View*, sf::Sprite* sprite);
            void deregisterAllSprites();
            std::vector<sf::Sprite*> getViewSprites(sf::View* view);

            void drawSprites(sf::RenderWindow* windowPtr);

        private:
            std::unordered_map<sf::View*, std::vector<sf::Sprite*>> m_sprites;
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
            void deregisterAllPhysicalObjects();
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
    class PhysicalObject{
        public:
            PhysicalObject(sf::Sprite* ownerSprite);

            
            sf::Sprite* getOwnerSprite();

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
            sf::Sprite* m_ownerSpritePtr;

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
            void registerCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionGroup);
            void deregisterCollisionGroup(std::string name);
            void registerCollisionGroups(std::unordered_map<std::string, std::vector<sge::CollisionShape*>> collisionGroups);
            void deregisterAllCollisionGroups();
            std::unordered_map<std::string, std::vector<sge::CollisionShape*>> getCollisionGroups();
            void deregisterCollisionShapeFromCollisionGroups(CollisionShape* collisionShape);

            void registerCollisionPair(std::string name, sge::CollisionPair* collisionPair);
            void deregisterCollisionPair(std::string name);
            void registerCollisionPairs(std::unordered_map<std::string, CollisionPair*> collisionPairs);
            void setCollisionPairsOrder(std::vector<std::string> order);
            void deregisterAllCollisionPairs();

            void updateCollisions();

        private:
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
        std::string initiatorGroupName;
        std::string recipientGroupName;
        
        std::function<void(std::vector<sge::Collision>)> startPhaseCollisionResponse;
        std::function<void(std::vector<sge::Collision>)> continuousPhaseCollisionResponse;
        std::function<void(std::vector<sge::Collision>)> endPhaseCollisionResponse;

        std::unordered_map<sge::CollisionShape*, std::vector<sge::Collision>> pastCollisions;
        
        std::function<bool(sge::CollisionShape *initiator, sge::CollisionShape *recipient)> algorithm;
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
            CollisionShape(sge::Entity* ownerEntity);

            sf::Vector2f offset = sf::Vector2f(0, 0);

            sge::Entity* getOwnerEntity();
            sge::Measurements getMeasurements();
            void align();

        private:
            sge::Entity* m_ownerEntityPtr;
    };
}

#endif
#ifndef COLLISION_SHAPE_MANAGER_H
#define COLLISION_SHAPE_MANAGER_H

#include <vector>

namespace sge{
    class CollisionShape;

    class CollisionShapeManager{
        public:
            void registerCollisionShape(sge::CollisionShape* collisionShape);
            void deregisterCollisionShape(sge::CollisionShape* collisionShape);
            void registerCollisionShapes(std::vector<sge::CollisionShape*> collisionShapes);
            void deregisterAllCollisionShapes();
            

            std::vector<sge::CollisionShape*> getCollisionShapes();
            
            
            void alignCollisionShapes();

        private:
            std::vector<CollisionShape*> m_collisionShapes;
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

#ifndef CLICKABLE_SHAPE_H
#define CLICKABLE_SHAPE_H

#include <functional>
#include <SFML/Graphics.hpp>

namespace sge{
    class Entity;

    class ClickableShape : public sf::RectangleShape{
        public:
            ClickableShape(sge::Entity* ownerEntity);

            std::function<void(sge::ClickableShape* thisClickableShape, sf::Event event)> action;
            
            sf::Vector2f offset = sf::Vector2f(0, 0);

            
            sge::Entity* getOwnerEntity();
            void align();

        private:
            sge::Entity* m_ownerEntityPtr;
    };
}

#endif
#ifndef CLICKABLE_SHAPE_MANAGER_H
#define CLICKABLE_SHAPE_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

namespace sge{
    struct ClickableShape;

    class ClickableShapeManager{
        public:
            void registerClickableShape(sf::View* view, sge::ClickableShape* clickableShape);
            void deregsiterClickableShape(sf::View* view, sge::ClickableShape* clickableShape);
            std::vector<sge::ClickableShape*> getClickableShapesByView(sf::View* view);
            std::unordered_map<sf::View*, std::vector<sge::ClickableShape*>> getClickableShapesMap();

            void alignClickableShapes();
            void updateClickableShapes(sf::Event event);

        private:
            std::unordered_map<sf::View*, std::vector<sge::ClickableShape*>> m_clickableShapes;
    };
}

#endif
#ifndef CLICKABLE_SHAPE_HELPERS_H
#define CLICKABLE_SHAPE_HELPERS_H

#include <SFML/Graphics.hpp>

namespace sge{
    class ClickableShape;

    bool isMouseOverClickableShape(ClickableShape* clickableShape, sf::RenderWindow* window);
}

#endif

#ifndef SPRITE_TEXT_H
#define SPRITE_TEXT_H

#include <SFML/Graphics.hpp>

namespace sge{
    class SpriteText : public sf::Text{
        public:
            SpriteText(sf::Sprite* ownerSprite);

            sf::Vector2f offset = sf::Vector2f(0, 0);

            void align();
        
        private:
            sf::Sprite* m_ownerSpritePtr;
    };
}

#endif
#ifndef SPRITE_TEXT_MANAGER_H
#define SPRITE_TEXT_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

namespace sge{
    class SpriteText;

    class SpriteTextManager{
        public:
            void registerSpriteText(sf::View* view, sge::SpriteText* spriteText);
            void deregisterSpriteText(sf::View* view, sge::SpriteText* spriteText);
            std::vector<sge::SpriteText*> getSpriteTextObjectsByView(sf::View* view);
            std::unordered_map<sf::View*, std::vector<sge::SpriteText*>> getSpriteTextObjectsMap();

            void alignSpriteTextObjects();
            void drawSpriteTextObjects(sf::RenderWindow* windowPtr);

        private:
            std::unordered_map<sf::View*, std::vector<sge::SpriteText*>> m_spriteTextObjects;
    };  
}

#endif

#include <vector>

namespace sge{
    class Animation;    

    class AnimationManager{
        public:
            void registerAnimation(sge::Animation* animation);
            void deregisterAnimation(sge::Animation* animation);
            void deregisterAllAnimations();

            void updateAnimations();

        private:
            std::vector<sge::Animation*> m_animations;
    };
}
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
            Animation(sge::TextureSheet* textureSheet, sf::Sprite* ownerSprite, int initialTextureN);
        
            int animationDelayMilliseconds = 100;
            
            void addTextureSequence(std::string name, std::vector<int> textureSequence);
            void setCurrentTextureSequence(std::string name);
        
            void runForward();
            // TODO
            // animationType : forward or cycle, run function in manager based on animation type
            // runCycle()  1 2 3 2 1

        private:
            sf::Sprite* m_ownerSpritePtr;
            sge::TextureSheet* m_textureSheet;
            
            sf::Clock m_clock;
            std::unordered_map<std::string, std::vector<int>> m_textureSequences; // e.g. "idle": [5, 6, 7, 8]
            std::string m_currentTextureSequence;
            int m_currentTextureN = 0;

    };
}

#endif

#ifndef ENTITY_H
#define ENTITY_H

namespace sge{
    class PhysicalObject;
    class CollisionShape;
    class ClickableShape;
    class SpriteText;
    class Animation;

    struct Entity{
        sf::Sprite* sprite;
        sge::PhysicalObject* physicalObject = nullptr;
        std::unordered_map<std::string, sge::CollisionShape*> collisionShapes; 
        sge::ClickableShape* clickableShape = nullptr;
        sge::SpriteText* spriteText = nullptr;
        sge::Animation* animation = nullptr;
    };
}

#endif
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

namespace sge{
    struct Entity;
    class SpriteManager;
    class PhysicsManager;
    class CollisionShapeManager;
    class ClickableShapeManager;
    class SpriteTextManager;
    class AnimationManager;
    class CollisionManager;

    class EntityManager{
        public:
            EntityManager(
                sge::SpriteManager* spriteManager,
                sge::PhysicsManager* physicsManager,
                sge::CollisionShapeManager* collisionShapeManager,
                sge::ClickableShapeManager* clickableShapeManager,
                sge::SpriteTextManager* SpriteTextManager,
                sge::AnimationManager* animationManager,
                sge::CollisionManager* collisionManager
            );

            void registerEntity(sf::View* view, sge::Entity* entity);
            void registerEntities(sf::View* view, std::vector<sge::Entity*> entities);
            void deregisterEntity(sf::View* view, sge::Entity* entity);
            void deregisterEntities(sf::View* view, std::vector<sge::Entity*> entities);
            void deregisterAllEntities();
            std::vector<sge::Entity*> getViewEntities(sf::View* view);

        private:
            std::unordered_map<sf::View*, std::vector<sge::Entity*>> m_entities;

            sge::SpriteManager* m_spriteManagerPtr;
            sge::PhysicsManager* m_physicsManagerPtr;
            sge::CollisionShapeManager* m_collisionShapeManagerPtr;
            sge::ClickableShapeManager* m_clickableShapeManagerPtr;
            sge::SpriteTextManager* m_spriteTextManagerPtr;
            sge::AnimationManager* m_animationManagerPtr;
            sge::CollisionManager* m_collisionManagerPtr;

            void m_deregisterEntityFromCoreManagers(sf::View* view, sge::Entity* entity);
    };
}

#endif
#ifndef ENTITY_BUILDERS_H
#define ENTITY_BUILDERS_H

#include <SFML/Graphics.hpp>

namespace sge{
    class Entity;
    
    // Builds sge::Entity that consists only of sf::Sprite*
    Entity* buildPlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);

    // Builds sge::Entity that consists of sf::Sprite* with empty textture and "globalBounds" -> sge::CollisionShape*
    Entity* buildVoidEntity(sf::Vector2f size, sf::Vector2f position);

    // Builds sge::Entity that consists of sf::Sprite* and "globalBounds" -> sge::CollisionShape*
    Entity* buildStaticEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);

    // Builds sge::Entity that consists of sf::Sprite*, sge::PhysicalObject* and "globalBounds" -> sge::CollisionShape*
    //
    // PhysicalObject added continuous computations:
    // "updateVelocity" -> updateVelocityBasedOnAcceleration()
    // "updatePosition" -> updatePositionBasedOnVelocity()
    Entity* buildMobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position);
}

#endif

#ifndef SCENE_H
#define SCENE_H

#include <unordered_map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

namespace sge{
    class Entity;
    class DebugEntity;
    class CollisionShape;
    struct CollisionPair;

    class Scene{
        public:
            void registerEntity(sf::View* view, sge::Entity* entity);
            void registerEntities(sf::View* view, std::vector<sge::Entity*> entities);
            void registerDebugEntity(sf::View* view, sge::DebugEntity* debugEntity);
            void registerDebugEntities(sf::View* view, std::vector<sge::DebugEntity*> debugEntities);
            void registerCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionShapes);
            void registerCollisionPair(std::string name, sge::CollisionPair* collisionPair);
        
        
            std::vector<sge::Entity*> getViewEntities(sf::View* view);
            std::unordered_map<sf::View*, std::vector<sge::Entity*>> getEntitiesMap();

            std::vector<sge::DebugEntity*> getViewDebugEntities(sf::View* view);
            std::unordered_map<sf::View*, std::vector<sge::DebugEntity*>> getDebugEntitiesMap();
            
            std::unordered_map<std::string, std::vector<sge::CollisionShape*>> getCollisionGroups();
            std::unordered_map<std::string, sge::CollisionPair*> getCollisionPairs();
            std::vector<std::string> getCollisionPairsOrder();

        private:
            std::unordered_map<sf::View*, std::vector<sge::Entity*>> m_entities;
            std::unordered_map<sf::View*, std::vector<sge::DebugEntity*>> m_debugEntities;
            std::unordered_map<std::string, std::vector<sge::CollisionShape*>> m_collisionGroups;
            std::unordered_map<std::string, sge::CollisionPair*> m_collisionPairs;
            std::vector<std::string> m_collisionPairsOrder;
    };
}

#endif
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <unordered_map>
#include <string>

namespace sge{
    class Scene;
    class EntityManager;
    class CollisionManager;
    class DebugManager;

    class SceneManager{
        public:
            SceneManager(sge::EntityManager* entityManager, sge::CollisionManager* collisionManager);

            void setupDebug(sge::DebugManager* debugManager);

            void registerScene(std::string name, sge::Scene* scene);
            void setCurrentScene(std::string name);
            void alignScene();
        
        private:
            std::unordered_map<std::string, sge::Scene*> m_scenes;
            std::string m_currentScene = "";
            std::string m_loadedScene = "";

            sge::EntityManager* m_entityManagerPtr = nullptr;
            sge::CollisionManager* m_collisionManagerPtr = nullptr;
            sge::DebugManager* m_debugManagerPtr = nullptr;
    };
}

#endif
//

// utils
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
//

#endif

#ifndef SGE_MAIN
#define SGE_MAIN

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
    sge::CollisionManager* CM = new sge::CollisionManager();
    sge::EntityManager* EM = new sge::EntityManager(SpM, PM, CSM, ClSM, STM, AnM, CM);
    sge::SceneManager* ScM = new sge::SceneManager(EM, CM);

    assetsManager = AsM;
    controllerManager = CoM;
    scriptedViewManager = VM;

    m_spriteManager = SpM;
    m_physicsManager = PM;
    m_collisionShapeManager = CSM;
    m_clickableShapeManager = ClSM;
    m_spriteTextManager = STM;
    m_animationManager = AnM;
    collisionManager = CM;
    entityManager = EM;
    sceneManager = ScM;
}

void sge::Universe::setupDebug(){
    sge::DebugManager* debugManagerPtr = new sge::DebugManager();
    debugManager = debugManagerPtr;

   sceneManager->setupDebug(debugManagerPtr);
}

void sge::Universe::loop(){
    if(!m_windowPtr){
        printf("RenderWindow is not initialized. Use setupWindow method to initialize RenderWindow before(!) looping the Universe.\n");
        exit(1);
    }

    m_deltaClock.restart();

    while(m_windowPtr->isOpen()){
        sf::Time deltaTime = m_deltaClock.restart();
        float dt = deltaTime.asSeconds();
        if(dt > 0.15f) dt = 0.15f;

        sf::Event event;
        while(m_windowPtr->pollEvent(event)){
            if(event.type == sf::Event::Closed) m_windowPtr->close();

            controllerManager->updateControllers(event);
            m_clickableShapeManager->updateClickableShapes(event);
        }

        if(!isPaused){
            m_physicsManager->updatePhysics(dt);
            m_collisionShapeManager->alignCollisionShapes();
            collisionManager->updateCollisions();
            m_animationManager->updateAnimations();
            scriptedViewManager->runViewScripts();
            sceneManager->alignScene(); // Scene can be reset only after all managers finished their updates to prevent segfaults
        }
        m_clickableShapeManager->alignClickableShapes();
        m_spriteTextManager->alignSpriteTextObjects();
        
        
        m_windowPtr->clear();
        
        m_spriteManager->drawSprites(m_windowPtr);
        m_spriteTextManager->drawSpriteTextObjects(m_windowPtr);
        debugManager->showDebugInfo(m_windowPtr);

        m_windowPtr->display();
    }
}


void sge::AssetsManager::loadTextureSheet(std::string location, std::string name, sge::TextureSheetSizes textureSheetSizes){ m_textures[name] = new sge::TextureSheet(textureSheetSizes, location); }
sge::TextureSheet* sge::AssetsManager::getTextureSheet(std::string name){ return m_textures[name]; }

void sge::AssetsManager::loadFont(std::string location, std::string name){
    sf::Font* font = new sf::Font;
    font->loadFromFile(location);

    m_fonts[name] = font;
}
sf::Font* sge::AssetsManager::getFont(std::string name){ return m_fonts[name]; }

void sge::AssetsManager::loadSFX(std::string location, std::string name){
    sf::SoundBuffer* buffer = new sf::SoundBuffer();
    buffer->loadFromFile(location);

    sf::Sound* sound = new sf::Sound(*buffer);
    m_sfx[name] = std::make_pair(buffer, sound);
}
sf::Sound* sge::AssetsManager::getSound(std::string name){ return m_sfx[name].second; }

void sge::AssetsManager::specifyMusicLocation(std::string location, std::string name){ m_musicLocations[name] = location; }
std::string sge::AssetsManager::getMusicLocation(std::string name){ return m_musicLocations[name]; }


sge::TextureSheet::TextureSheet(sge::TextureSheetSizes textureSheetSizes, std::string location){
    m_location = location;
    m_textureSheet.loadFromFile(location);

    for(int i = 0; i < textureSheetSizes.numTexturesY*textureSheetSizes.textureSizeY; i += textureSheetSizes.textureSizeY+textureSheetSizes.gapY){
        for(int j = 0; j < textureSheetSizes.numTexturesX*textureSheetSizes.textureSizeX; j += textureSheetSizes.textureSizeX+textureSheetSizes.gapX){
            m_textureRects.push_back(sf::IntRect(j, i, textureSheetSizes.textureSizeX, textureSheetSizes.textureSizeY));
        }
    }
}

std::string sge::TextureSheet::getLocation(){ return m_location; }
sf::Texture* sge::TextureSheet::getTexture(){ return &m_textureSheet; }
sf::IntRect sge::TextureSheet::getTextureRect(int textureN){ return m_textureRects[textureN]; }


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


void sge::DebugManager::registerDebugEntity(sf::View* view, sge::DebugEntity* debugEntity){ m_debugEntities[view].push_back(debugEntity); }
void sge::DebugManager::registerDebugEntities(sf::View* view, std::vector<sge::DebugEntity*> debugEntities){
    for(DebugEntity* debugEntity : debugEntities){
        registerDebugEntity(view, debugEntity);
    }
}
void sge::DebugManager::deregisterDebugEntity(sf::View* view, sge::DebugEntity* debugEntity){ m_debugEntities[view].erase(std::remove(m_debugEntities[view].begin(), m_debugEntities[view].end(), debugEntity), m_debugEntities[view].end()); }
void sge::DebugManager::deregisterAllDebugEntities(){ m_debugEntities.clear(); }

void sge::DebugManager::showDebugInfo(sf::RenderWindow* windowPtr){
    for(auto& [view, debugEntities]: m_debugEntities){
        windowPtr->setView(*view);
        
        for(sge::DebugEntity* debugEntity : debugEntities){
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
}


sge::CollisionShapeBorder::CollisionShapeBorder(sge::CollisionShape* owner, sge::CollisionShapeBorderSettings settings){
    this->setFillColor(sf::Color(0,0,0,0));

    this->setOutlineColor(settings.color);
    this->setOutlineThickness(settings.thickness);

    this->setPosition(sf::Vector2f(owner->getPosition().x + settings.thickness, owner->getPosition().y + settings.thickness));
    this->setSize(sf::Vector2f(owner->getSize().x - settings.thickness*2, owner->getSize().y - settings.thickness*2));
}


void sge::ControllerManager::registerController(std::function<void(sf::Event)> controller){ m_controllers.push_back(controller); }
std::vector<std::function<void(sf::Event)>> sge::ControllerManager::getAllControllers(){ return m_controllers; }

void sge::ControllerManager::updateControllers(sf::Event event){
    for(std::function<void(sf::Event)> controller : m_controllers){
        controller(event);
    }
}


void sge::ScriptedViewManager::registerScriptedView(sge::ScriptedView* scriptedView){ m_scriptedViews.push_back(scriptedView); }

void sge::ScriptedViewManager::runViewScripts(){
    for(sge::ScriptedView* scriptedView : m_scriptedViews){
        if(scriptedView->script){
            scriptedView->script(scriptedView);
        }
    }
}


void sge::SpriteManager::registerSprite(sf::View* view, sf::Sprite* sprite){ m_sprites[view].push_back(sprite); }
void sge::SpriteManager::deregisterSprite(sf::View* view, sf::Sprite* sprite){ m_sprites[view].erase(std::remove(m_sprites[view].begin(), m_sprites[view].end(), sprite), m_sprites[view].end()); }
void sge::SpriteManager::deregisterAllSprites(){ m_sprites.clear(); }
std::vector<sf::Sprite*> sge::SpriteManager::getViewSprites(sf::View* view){ return m_sprites[view]; }

void sge::SpriteManager::drawSprites(sf::RenderWindow* windowPtr){
    for(auto [view, sprites] : m_sprites){
        windowPtr->setView(*view);

        for(sf::Sprite* sprite : sprites){
            windowPtr->draw(*sprite);
        }
    }
}


void sge::PhysicsManager::registerPhysicalObject(sge::PhysicalObject* physicalObject){ m_physicalObjects.push_back(physicalObject); }
void sge::PhysicsManager::deregisterPhysicalObject(sge::PhysicalObject* physicalObject){ m_physicalObjects.erase(std::remove(m_physicalObjects.begin(), m_physicalObjects.end(), physicalObject), m_physicalObjects.end()); }
void sge::PhysicsManager::deregisterAllPhysicalObjects(){ m_physicalObjects.clear(); }
std::vector<sge::PhysicalObject*> sge::PhysicsManager::getAllPhysicalObjects(){ return m_physicalObjects; }

void sge::PhysicsManager::updatePhysics(float dt){
    for(sge::PhysicalObject* physicalObject : m_physicalObjects){
        physicalObject->update(dt);
    }
}


sge::PhysicalObject::PhysicalObject(sf::Sprite* ownerSprite){ m_ownerSpritePtr = ownerSprite; }

sf::Sprite* sge::PhysicalObject::getOwnerSprite(){ return m_ownerSpritePtr; }

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
        thisPhysicalObject->getOwnerSprite()->setPosition(thisPhysicalObject->getOwnerSprite()->getPosition() + thisPhysicalObject->velocity * dt);
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
#include <algorithm>

void sge::CollisionManager::registerCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionGroup){ m_collisionGroups[name] = collisionGroup; } 
void sge::CollisionManager::deregisterCollisionGroup(std::string name){
    // Remove related collision pairs
    std::vector<std::string> pairsToRemove;
    for(auto& [pairName, collisionPair] : m_collisionPairs){
        if(collisionPair->initiatorGroupName == name || collisionPair->recipientGroupName == name){
            pairsToRemove.push_back(pairName);
        }
    }
    for(std::string pairToRemove : pairsToRemove){
        deregisterCollisionPair(pairToRemove);
    }
    //

    m_collisionGroups.erase(name);
}
void sge::CollisionManager::registerCollisionGroups(std::unordered_map<std::string, std::vector<sge::CollisionShape*>> collisionGroups){ m_collisionGroups.insert(collisionGroups.begin(), collisionGroups.end()); }
void sge::CollisionManager::deregisterAllCollisionGroups(){
    m_collisionGroups.clear();
    m_collisionPairs.clear();
}
std::unordered_map<std::string, std::vector<sge::CollisionShape*>> sge::CollisionManager::getCollisionGroups(){ return m_collisionGroups; }
void sge::CollisionManager::deregisterCollisionShapeFromCollisionGroups(CollisionShape* collisionShape){
    for(auto [_, collisionGroup] : m_collisionGroups){
        collisionGroup.erase(std::remove(collisionGroup.begin(), collisionGroup.end(), collisionShape), collisionGroup.end());
    }
}

void sge::CollisionManager::registerCollisionPair(std::string name, sge::CollisionPair* collisionPair){
    m_collisionPairs[name] = collisionPair;
    m_collisionPairsOrder.push_back(name);
};
void sge::CollisionManager::registerCollisionPairs(std::unordered_map<std::string, CollisionPair*> collisionPairs){ m_collisionPairs.insert(collisionPairs.begin(), collisionPairs.end()); }
void sge::CollisionManager::setCollisionPairsOrder(std::vector<std::string> order){ m_collisionPairsOrder = order; }
void sge::CollisionManager::deregisterCollisionPair(std::string name){
    m_collisionPairs.erase(name);
    m_collisionPairsOrder.erase(std::remove(m_collisionPairsOrder.begin(), m_collisionPairsOrder.end(), name), m_collisionPairsOrder.end());
}
void sge::CollisionManager::deregisterAllCollisionPairs(){
    m_collisionPairs.clear();
    m_collisionPairsOrder.clear();
}

void sge::CollisionManager::updateCollisions(){
    std::vector<sge::Collision> presentCollisions;

    for(std::string pair : m_collisionPairsOrder){

        for(sge::CollisionShape* initiator : m_collisionGroups[m_collisionPairs[pair]->initiatorGroupName]){
            // Register all present collisions
            for(sge::CollisionShape* recipient : m_collisionGroups[m_collisionPairs[pair]->recipientGroupName]){
                if(m_collisionPairs[pair]->algorithm(initiator, recipient)){
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


sge::CollisionShape::CollisionShape(sge::Entity* ownerEntity){
    m_ownerEntityPtr = ownerEntity;

    this->setFillColor(sf::Color(0,0,0,0));
    this->setSize(sf::Vector2f(ownerEntity->sprite->getGlobalBounds().width, ownerEntity->sprite->getGlobalBounds().height));
}

sge::Entity* sge::CollisionShape::getOwnerEntity(){ return m_ownerEntityPtr; }
sge::Measurements sge::CollisionShape::getMeasurements(){
    return { this->getPosition().x, this->getPosition().y, this->getGlobalBounds().height, this->getGlobalBounds().width };
}
void sge::CollisionShape::align(){
    this->setPosition(m_ownerEntityPtr->sprite->getPosition() + offset);
}
#include <algorithm>

void sge::CollisionShapeManager::registerCollisionShape(sge::CollisionShape* collisionShape){ m_collisionShapes.push_back(collisionShape); }
void sge::CollisionShapeManager::deregisterCollisionShape(sge::CollisionShape* collisionShape){ m_collisionShapes.erase(std::remove(m_collisionShapes.begin(), m_collisionShapes.end(), collisionShape), m_collisionShapes.end()); }
void sge::CollisionShapeManager::registerCollisionShapes(std::vector<sge::CollisionShape*> collisionShapes){ m_collisionShapes.insert(m_collisionShapes.end(), collisionShapes.begin(), collisionShapes.end()); }
void sge::CollisionShapeManager::deregisterAllCollisionShapes(){ m_collisionShapes.clear(); }

std::vector<sge::CollisionShape*> sge::CollisionShapeManager::getCollisionShapes(){ return m_collisionShapes; }

void sge::CollisionShapeManager::alignCollisionShapes(){
    for(sge::CollisionShape* collisionShape : m_collisionShapes){
        collisionShape->align();
    }
}


void sge::resolveAABB(std::vector<sge::Collision> collisions){
    for(sge::Collision collision : collisions){
        sge::CollisionShape* initiatorCollisionShape = collision.initiator;
        sge::CollisionShape* recipientCollisionShape = collision.recipient;
        sf::Sprite *initiatorSprite = collision.initiator->getOwnerEntity()->sprite;
        sf::Sprite *recipientSprite = collision.recipient->getOwnerEntity()->sprite;
        
        // Align initiator based on impact side
        if(collision.initiatorImpactSide == sge::CollisionSide::left){
            initiatorSprite->setPosition(
                recipientSprite->getPosition().x + recipientSprite->getGlobalBounds().width - collision.initiator->offset.x + collision.recipient->offset.x,
                initiatorSprite->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::right){
            initiatorSprite->setPosition(
                recipientSprite->getPosition().x - collision.initiator->getGlobalBounds().width - collision.initiator->offset.x + collision.recipient->offset.x,
                initiatorSprite->getPosition().y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::top){
            initiatorSprite->setPosition(
                initiatorSprite->getPosition().x,
                recipientSprite->getPosition().y + recipientSprite->getGlobalBounds().height - collision.initiator->offset.y + collision.recipient->offset.y
            );
        }
        else if(collision.initiatorImpactSide == sge::CollisionSide::bottom){
            initiatorSprite->setPosition(
                initiatorSprite->getPosition().x,
                recipientSprite->getPosition().y - collision.initiator->getGlobalBounds().height - collision.initiator->offset.y + collision.recipient->offset.y
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


sge::ClickableShape::ClickableShape(sge::Entity* ownerUIEntity){ m_ownerEntityPtr = ownerUIEntity; }

sge::Entity* sge::ClickableShape::getOwnerEntity(){ return m_ownerEntityPtr; }
void sge::ClickableShape::align(){ this->setPosition(m_ownerEntityPtr->sprite->getPosition() + offset); }
#include <algorithm>
#include <SFML/Graphics.hpp>

void sge::ClickableShapeManager::registerClickableShape(sf::View* view, sge::ClickableShape* clickableShape){ m_clickableShapes[view].push_back(clickableShape); }
void sge::ClickableShapeManager::deregsiterClickableShape(sf::View* view, sge::ClickableShape* clickableShape){
    m_clickableShapes[view].erase(std::remove(m_clickableShapes[view].begin(), m_clickableShapes[view].end(), clickableShape), m_clickableShapes[view].end());
}
std::vector<sge::ClickableShape*> sge::ClickableShapeManager::getClickableShapesByView(sf::View* view){ return m_clickableShapes[view]; }
std::unordered_map<sf::View*, std::vector<sge::ClickableShape*>> sge::ClickableShapeManager::getClickableShapesMap(){ return m_clickableShapes; };

void sge::ClickableShapeManager::alignClickableShapes(){
    for(auto& [_, clickableShapes] : m_clickableShapes){
        for(sge::ClickableShape* clickableShape : clickableShapes){
            clickableShape->align();
        }
    }
}

void sge::ClickableShapeManager::updateClickableShapes(sf::Event event){
    for(auto& [_, clickableShapes] : m_clickableShapes){
        for(ClickableShape* thisClickableShape : clickableShapes){
            thisClickableShape->action(thisClickableShape, event);
        }
    }
}


bool sge::isMouseOverClickableShape(ClickableShape* clickableShape, sf::RenderWindow* window){
    return clickableShape->getOwnerEntity()->sprite->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
}


sge::SpriteText::SpriteText(sf::Sprite* ownerSprite){ m_ownerSpritePtr = ownerSprite; }
void sge::SpriteText::align(){
    sf::Vector2f pos = m_ownerSpritePtr->getPosition() + offset; 
    
    this->setPosition((int)pos.x, (int)pos.y);
}
#include <algorithm>

void sge::SpriteTextManager::registerSpriteText(sf::View* view, sge::SpriteText* spriteText){ m_spriteTextObjects[view].push_back(spriteText); }
void sge::SpriteTextManager::deregisterSpriteText(sf::View* view, sge::SpriteText* spriteText){
    m_spriteTextObjects[view].erase(std::remove(m_spriteTextObjects[view].begin(), m_spriteTextObjects[view].end(), spriteText), m_spriteTextObjects[view].end());
}
std::vector<sge::SpriteText*> sge::SpriteTextManager::getSpriteTextObjectsByView(sf::View* view){ return m_spriteTextObjects[view]; }
std::unordered_map<sf::View*, std::vector<sge::SpriteText*>> sge::SpriteTextManager::getSpriteTextObjectsMap(){ return m_spriteTextObjects; }

void sge::SpriteTextManager::alignSpriteTextObjects(){
    for(auto& [_, spriteTextObjects] : m_spriteTextObjects){
        for(sge::SpriteText* spriteText : spriteTextObjects){
            spriteText->align();
        }
    }
}
void sge::SpriteTextManager::drawSpriteTextObjects(sf::RenderWindow* windowPtr){
    for(auto& [view, spriteTextObjects] : m_spriteTextObjects){
        windowPtr->setView(*view);

        for(SpriteText* spriteText : spriteTextObjects){
            windowPtr->draw(*spriteText);
        }
    }
}


void sge::AnimationManager::registerAnimation(sge::Animation* animation){ m_animations.push_back(animation); }
void sge::AnimationManager::deregisterAnimation(sge::Animation* animation){ m_animations.erase(std::remove(m_animations.begin(), m_animations.end(), animation), m_animations.end()); }
void sge::AnimationManager::deregisterAllAnimations(){ m_animations.clear(); }

void sge::AnimationManager::updateAnimations(){
    for(sge::Animation* animation : m_animations){
        animation->runForward();
    }
}


sge::Animation::Animation(sge::TextureSheet* textureSheet, sf::Sprite* ownerSprite, int initialTextureN){
    m_textureSheet = textureSheet;
    m_ownerSpritePtr = ownerSprite;
    
    m_ownerSpritePtr->setTexture(*textureSheet->getTexture());
    m_ownerSpritePtr->setTextureRect(textureSheet->getTextureRect(initialTextureN));
}

void sge::Animation::addTextureSequence(std::string name, std::vector<int> textureSequence){ m_textureSequences[name] = textureSequence; }
void sge::Animation::setCurrentTextureSequence(std::string name){
    m_clock.restart();
    m_currentTextureSequence = name;
    m_currentTextureN = 0;

    m_ownerSpritePtr->setTextureRect(m_textureSheet->getTextureRect(m_textureSequences[m_currentTextureSequence].at(m_currentTextureN)));
}

void sge::Animation::runForward(){
    if(!m_textureSequences.size()){
        printf("No texture sequences initialized.\n");
        exit(1);
    }
    if(!m_currentTextureSequence.length()){
        printf("Can not run animation if no current texture sequence is set.\n"); // ? Default to first added ?
        exit(1);
    }

    if(m_clock.getElapsedTime().asMilliseconds() > animationDelayMilliseconds){
        m_ownerSpritePtr->setTextureRect(m_textureSheet->getTextureRect(m_textureSequences[m_currentTextureSequence].at(m_currentTextureN)));
        
        if(m_currentTextureN+1 == m_textureSequences[m_currentTextureSequence].size()){
            m_currentTextureN = 0;
        }
        else m_currentTextureN++;

        m_clock.restart();
    }
}


sge::EntityManager::EntityManager(sge::SpriteManager* spriteManager, sge::PhysicsManager* physicsManager, sge::CollisionShapeManager* collisionShapeManager, sge::ClickableShapeManager* clickableShapeManager, sge::SpriteTextManager* spriteTextManager, sge::AnimationManager* animationManager, sge::CollisionManager* collisionManager){
    m_spriteManagerPtr = spriteManager;
    m_physicsManagerPtr = physicsManager;
    m_collisionShapeManagerPtr = collisionShapeManager;
    m_clickableShapeManagerPtr = clickableShapeManager;
    m_spriteTextManagerPtr = spriteTextManager;
    m_animationManagerPtr = animationManager;
    m_collisionManagerPtr = collisionManager;
}

void sge::EntityManager::registerEntity(sf::View* view, sge::Entity* entity){
    m_spriteManagerPtr->registerSprite(view, entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->registerPhysicalObject(entity->physicalObject);
    }
        
    if(entity->collisionShapes.size()){
        for(auto& [_, collisionShape] : entity->collisionShapes){
            m_collisionShapeManagerPtr->registerCollisionShape(collisionShape);
        }
    }

    if(entity->clickableShape){
        m_clickableShapeManagerPtr->registerClickableShape(view, entity->clickableShape);
    }

    if(entity->spriteText){
        m_spriteTextManagerPtr->registerSpriteText(view, entity->spriteText);
    }
    
    if(entity->animation){
        m_animationManagerPtr->registerAnimation(entity->animation);
    }

    m_entities[view].push_back(entity);
}

void sge::EntityManager::registerEntities(sf::View* view, std::vector<sge::Entity*> entities){
    for(sge::Entity* entity : entities){
        registerEntity(view, entity);
    }
}

void sge::EntityManager::deregisterEntity(sf::View* view, sge::Entity* entity){
    m_deregisterEntityFromCoreManagers(view, entity);

    m_entities[view].erase(std::remove(m_entities[view].begin(), m_entities[view].end(), entity), m_entities[view].end());    
}

void sge::EntityManager::deregisterEntities(sf::View* view, std::vector<sge::Entity*> entities){
    for(sge::Entity* entity : entities){
        deregisterEntity(view, entity);
    }
}

void sge::EntityManager::deregisterAllEntities(){
    for(auto& [view, entities] : m_entities){
        for(Entity* entity : entities){
            m_deregisterEntityFromCoreManagers(view, entity);
        }
    }

    m_entities.clear();
}

std::vector<sge::Entity*> sge::EntityManager::getViewEntities(sf::View* view){ return m_entities[view]; }

void sge::EntityManager::m_deregisterEntityFromCoreManagers(sf::View* view, sge::Entity* entity){
    m_spriteManagerPtr->deregisterSprite(view, entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->deregisterPhysicalObject(entity->physicalObject);
    }

    if(entity->collisionShapes.size()){
        for(auto[_, collisionShape] : entity->collisionShapes){
            m_collisionShapeManagerPtr->deregisterCollisionShape(collisionShape);
            m_collisionManagerPtr->deregisterCollisionShapeFromCollisionGroups(collisionShape);
        }
    }

    if(entity->clickableShape){
        m_clickableShapeManagerPtr->deregsiterClickableShape(view, entity->clickableShape);
    }

    if(entity->spriteText){
        m_spriteTextManagerPtr->deregisterSpriteText(view, entity->spriteText);
    }

    if(entity->animation){
        m_animationManagerPtr->deregisterAnimation(entity->animation);
    }
}


sge::Entity* sge::buildPlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    sge::Entity* e = new sge::Entity{ new sf::Sprite() };
    e->sprite->setTexture(*texture);
    e->sprite->setTextureRect(textureRect);
    e->sprite->setPosition(position);

    return e;
}

sge::Entity* sge::buildVoidEntity(sf::Vector2f size, sf::Vector2f position){
    sge::Entity* e = new sge::Entity{ new sf::Sprite() };
    e->sprite->setPosition(position);

    e->collisionShapes["globalBounds"] = new sge::CollisionShape(e);
    e->collisionShapes["globalBounds"]->setSize(size);

    return e;
}

sge::Entity* sge::buildStaticEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    sge::Entity* e = sge::buildPlainEntity(texture, textureRect, position);

    e->collisionShapes["globalBounds"] = new sge::CollisionShape(e);

    return e;
}

sge::Entity* sge::buildMobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
    sge::Entity* e = sge::buildStaticEntity(texture, textureRect, position);

    e->physicalObject = new PhysicalObject(e->sprite);

    e->physicalObject->createContinuousComputation("updateVelocity", sge::updateVelocityBasedOnAcceleration());
    e->physicalObject->createContinuousComputation("updatePosition", sge::updatePositionBasedOnVelocity());

    return e;
}


void sge::Scene::registerEntity(sf::View* view, sge::Entity* entity){ m_entities[view].push_back(entity); }
void sge::Scene::registerEntities(sf::View* view, std::vector<sge::Entity*> entities){
    for(Entity* entity : entities){
        registerEntity(view, entity);
    }
}
void sge::Scene::registerDebugEntity(sf::View* view, sge::DebugEntity* debugEntity){ m_debugEntities[view].push_back(debugEntity); }
void sge::Scene::registerDebugEntities(sf::View* view,std::vector<DebugEntity*> debugEntities){
    for(DebugEntity* debugEntity : debugEntities){
        registerDebugEntity(view, debugEntity);
    }
}
void sge::Scene::registerCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionShapes){ m_collisionGroups[name] = collisionShapes; }
void sge::Scene::registerCollisionPair(std::string name, sge::CollisionPair* collisionPair){
    m_collisionPairs[name] = collisionPair;
    m_collisionPairsOrder.push_back(name);
}

std::vector<sge::Entity*> sge::Scene::getViewEntities(sf::View* view){ return m_entities[view]; }
std::unordered_map<sf::View*, std::vector<sge::Entity*>> sge::Scene::getEntitiesMap(){ return m_entities; };

std::vector<sge::DebugEntity*> sge::Scene::getViewDebugEntities(sf::View* view){ return m_debugEntities[view]; }
std::unordered_map<sf::View*, std::vector<sge::DebugEntity*>> sge::Scene::getDebugEntitiesMap(){ return m_debugEntities; }

std::unordered_map<std::string, std::vector<sge::CollisionShape*>> sge::Scene::getCollisionGroups(){ return m_collisionGroups; };
std::unordered_map<std::string, sge::CollisionPair*> sge::Scene::getCollisionPairs(){ return m_collisionPairs; }
std::vector<std::string> sge::Scene::getCollisionPairsOrder(){ return m_collisionPairsOrder; };


sge::SceneManager::SceneManager(sge::EntityManager* entityManager, sge::CollisionManager* collisionManager){
    m_collisionManagerPtr = collisionManager;
    m_entityManagerPtr = entityManager;
}

void sge::SceneManager::setupDebug(sge::DebugManager* debugManager){ m_debugManagerPtr = debugManager; }

void sge::SceneManager::registerScene(std::string name, sge::Scene* scene){ m_scenes[name] = scene; }
void sge::SceneManager::setCurrentScene(std::string name){ m_currentScene = name; }
void sge::SceneManager::alignScene(){
    if(m_currentScene.length()){
        if(m_loadedScene != m_currentScene){
            // Reset
            for(auto& [view, entities] : m_scenes[m_loadedScene]->getEntitiesMap()){
                m_entityManagerPtr->deregisterEntities(view, entities);
            }
            //

            // Register new scene members
            for(auto& [view, entities] : m_scenes[m_currentScene]->getEntitiesMap()){
                m_entityManagerPtr->registerEntities(view, entities);
            }
            m_collisionManagerPtr->registerCollisionGroups(m_scenes[m_currentScene]->getCollisionGroups());
            m_collisionManagerPtr->registerCollisionPairs(m_scenes[m_currentScene]->getCollisionPairs());
            m_collisionManagerPtr->setCollisionPairsOrder(m_scenes[m_currentScene]->getCollisionPairsOrder());
            //

            // Register debug members
            if(m_debugManagerPtr){
                m_debugManagerPtr->deregisterAllDebugEntities();

                for(auto& [view, debugEntities] : m_scenes[m_currentScene]->getDebugEntitiesMap()){
                    m_debugManagerPtr->registerDebugEntities(view, debugEntities);
                }
            }
            //

            m_loadedScene = m_currentScene;
        }
    }
}


#endif