#ifndef SGE_HPP
#define SGE_HPP

#include <SFML/Graphics.hpp>

#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

namespace sge{
    class AssetsManager;
    class ControllerManager;

    class SpriteManager;
    class PhysicsManager;
    class PhysicalObject;
    class CollisionShapeManager;
    class AnimationManager;
    class CollisionManager;
    class EntityManager;
    class DebugManager;
    class SceneManager;
    
    class UISpriteManager;
    class ClickableShapeManager;
    class SpriteTextManager;
    class UIAnimationManager;
    class UIEntityManager;

    class Universe{
        public:
            Universe();

            bool isPaused = false;

            void setupWindow(sf::RenderWindow* window);
            void loop();

            sge::AssetsManager* assetsManager = nullptr;
            sge::ControllerManager* controllerManager = nullptr;

            sge::SpriteManager* spriteManager = nullptr;
            sge::PhysicsManager* physicsManager = nullptr;
            sge::CollisionShapeManager* collisionShapeManager = nullptr;
            sge::AnimationManager* animationManager = nullptr;
            sge::CollisionManager* collisionManager = nullptr;
            sge::EntityManager* entityManager = nullptr;
            sge::DebugManager* debugManager = nullptr;
            sge::SceneManager* sceneManager = nullptr;

            sge::UISpriteManager* uiSpriteManager = nullptr;
            sge::ClickableShapeManager* clickableShapeManager = nullptr;
            sge::SpriteTextManager* spriteTextManager = nullptr;
            sge::UIAnimationManager* uiAnimationManager = nullptr;
            sge::UIEntityManager* uiEntityManager = nullptr;

        private:
            sf::RenderWindow* m_windowPtr;

            sf::Clock m_deltaClock;
    };
}

#endif

// AssetsManager
#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include <unordered_map>
#include <string>

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
    class TextureSheet;

    class AssetsManager{
        public:
            void loadTextureSheet(std::string location, std::string name, sge::TextureSheetSizes textureSheetSizes);
            sge::TextureSheet* getTextureSheet(std::string name);

            void loadFont(std::string location, std::string name);
            sf::Font* getFont(std::string name);

        private:
            std::unordered_map<std::string, sge::TextureSheet*> m_textures;
            std::unordered_map<std::string, sf::Font*> m_fonts;
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

// ControllerManager
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

// Common
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

#ifndef CLICKABLE_SHAPE_H
#define CLICKABLE_SHAPE_H

#include <functional>
#include <SFML/Graphics.hpp>
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

namespace sge{
    class UIEntity;

    class ClickableShape : public sf::RectangleShape{
        public:
            ClickableShape(sge::UIEntity* ownerUIEntity);

            std::function<void(sge::ClickableShape* thisClickableShape, sf::Event event)> action;
            
            sf::Vector2f offset = sf::Vector2f(0, 0);

            
            sge::UIEntity* getOwnerUIEntity();
            void align();

        private:
            sge::UIEntity* m_ownerUIEntityPtr;
    };
}

#endif
#ifndef CLICKABLE_SHAPE_MANAGER_H
#define CLICKABLE_SHAPE_MANAGER_H

#include <vector>

namespace sge{
    struct ClickableShape;

    class ClickableShapeManager{
        public:
            void registerClickableShape(sge::ClickableShape* clickableShape);
            void deregsiterClickableShape(sge::ClickableShape* clickableShape);
            std::vector<sge::ClickableShape*> getAllActiveClickableShapes();

            void activateClickableShape(sge::ClickableShape* clickableShape);
            void deactivateClickableShape(sge::ClickableShape* clickableShape);

            void alignClickableShapes();

        private:
            std::vector<sge::ClickableShape*> m_activeClickableShapes;
            std::vector<sge::ClickableShape*> m_inactiveClickableShapes;
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
//

// Logic
#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>

namespace sge{
    class SpriteManager{
        public:
            void registerSprite(sf::Sprite* sprite);
            void deregisterSprite(sf::Sprite* sprite);
            void deregisterAllSprites();
            std::vector<sf::Sprite*> getSprites();            

        private:
            std::vector<sf::Sprite*> m_sprites;
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

#ifndef ENTITY_H
#define ENTITY_H

namespace sge{
    class PhysicalObject;
    class CollisionShape;
    class Animation;

    struct Entity{
        sf::Sprite* sprite;
        sge::PhysicalObject* physicalObject = nullptr;
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
    class SpriteManager;
    class PhysicsManager;
    class CollisionShapeManager;
    class AnimationManager;
    class CollisionManager;

    class EntityManager{
        public:
            EntityManager(sge::SpriteManager* spriteManager, sge::PhysicsManager* physicsManager, sge::CollisionShapeManager* collisionShapeManager, sge::AnimationManager* animationManager, sge::CollisionManager* collisionManager);

            void registerEntity(sge::Entity* entity);
            void registerEntities(std::vector<sge::Entity*> entities);
            void deregisterEntity(sge::Entity* entity);
            void deregisterAllEntities();
            std::vector<sge::Entity*> getAllEntities();

        private:
            std::vector<sge::Entity*> m_entities;

            sge::SpriteManager* m_spriteManagerPtr;
            sge::PhysicsManager* m_physicsManagerPtr;
            sge::CollisionShapeManager* m_collisionShapeManager;
            sge::AnimationManager* m_animationManagerPtr;
            sge::CollisionManager* m_collisionManager;

            void m_deregisterEntityFromCoreManagers(sge::Entity* entity);
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
            void registerDebugEntities(std::vector<sge::DebugEntity*> debugEntities);
            void deregisterDebugEntity(sge::DebugEntity* debugEntity);
            void deregisterAllDebugEntities();

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

#ifndef SCENE_H
#define SCENE_H

#include <unordered_map>
#include <vector>
#include <string>

namespace sge{
    class Entity;
    class DebugEntity;
    class CollisionShape;
    struct CollisionPair;

    class Scene{
        public:
            void registerEntity(sge::Entity* entity);
            void registerEntities(std::vector<sge::Entity*> entities);
            void registerDebugEntity(sge::DebugEntity* debugEntity);
            void registerDebugEntities(std::vector<sge::DebugEntity*> debugEntities);
            void registerCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionShapes);
            void registerCollisionPair(std::string name, sge::CollisionPair* collisionPair);
        
        
            std::vector<sge::Entity*> getEntities();
            std::vector<sge::DebugEntity*> getDebugEntities();
            std::unordered_map<std::string, std::vector<sge::CollisionShape*>> getCollisionGroups();
            std::unordered_map<std::string, sge::CollisionPair*> getCollisionPairs();
            std::vector<std::string> getCollisionPairsOrder();

        private:
            std::vector<sge::Entity*> m_entities;
            std::vector<sge::DebugEntity*> m_debugEntities;
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
    class SpriteManager;
    class PhysicsManager;
    class CollisionShapeManager;
    class AnimationManager;
    class CollisionManager;
    class EntityManager;
    class DebugManager;
    class Scene;

    class SceneManager{
        public:
            SceneManager(
                sge::SpriteManager* spriteManager,
                sge::PhysicsManager* physicsManager,
                sge::CollisionShapeManager* collisionShapeManager,
                sge::AnimationManager* animationManager,
                sge::CollisionManager* collisionManager,
                sge::EntityManager* entityManager,
                sge::DebugManager* debugManager
            );

            void registerScene(std::string name, sge::Scene* scene);
            void setCurrentScene(std::string name);
            void alignScene();
        
        private:
            std::unordered_map<std::string, sge::Scene*> m_scenes;
            std::string m_currentScene = "";
            std::string m_loadedScene = "";

            sge::SpriteManager* m_spriteManagerPtr;
            sge::PhysicsManager* m_physicsManagerPtr;
            sge::CollisionShapeManager* m_collisionShapeManagerPtr;
            sge::AnimationManager* m_animationManagerPtr;
            sge::CollisionManager* m_collisionManagerPtr;
            sge::EntityManager* m_entityManagerPtr;
            sge::DebugManager* m_debugManagerPtr;
    };
}

#endif
//

// UI
#ifndef UI_SPRITE_MANAGER_H
#define UI_SPRITE_MANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>

namespace sge{
    class UISpriteManager{
        public:
            void registerSprite(sf::Sprite* sprite);
            void deregisterSprite(sf::Sprite* sprite);
            std::vector<sf::Sprite*> getAllVisibleSprites();

            void showSprite(sf::Sprite* sprite);
            void hideSprite(sf::Sprite* sprite);

        private:
            std::vector<sf::Sprite*> m_visibleSprites;
            std::vector<sf::Sprite*> m_hiddenSprites;
    };
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

#include <vector>

namespace sge{
    class SpriteText;

    class SpriteTextManager{
        public:
            void registerSpriteText(sge::SpriteText* spriteText);
            void deregisterSpriteText(sge::SpriteText* spriteText);
            std::vector<sge::SpriteText*> getAllVisibleSpriteTextObjects();

            void showSpriteText(sge::SpriteText* spriteText);
            void hideSpriteText(sge::SpriteText* spriteText);

            void alignSpriteTextObjects();

        private:
            std::vector<sge::SpriteText*> m_visibleSpriteTextObjects;
            std::vector<sge::SpriteText*> m_hiddenSpriteTextObjects;
    };  
}

#endif

#ifndef UI_ENTITY_H
#define UI_ENTITY_H

#include <SFML/Graphics.hpp>

namespace sge{
    struct ClickableShape;
    class SpriteText;
    class Animation;

    struct UIEntity{
        sf::Sprite* sprite;
        sge::ClickableShape* clickableShape = nullptr;
        sge::SpriteText* spriteText = nullptr;
        sge::Animation* animation = nullptr;
    };
}

#endif
#ifndef UI_ENTITY_MANAGER_H
#define UI_ENTITY_MANAGER_H

#include <vector>

namespace sge{
    class UISpriteManager;
    class ClickableShapeManager;
    class SpriteTextManager;
    class UIAnimationManager;
    struct UIEntity;

    class UIEntityManager{
        public:
            UIEntityManager(sge::UISpriteManager* uiSpriteManager, sge::ClickableShapeManager* clickableShapeManager, sge::SpriteTextManager* spriteTextManager, sge::UIAnimationManager* uiAnimationManager);

            void registerUIEntity(sge::UIEntity* uiEntity);
            void deregisterUIEntity(sge::UIEntity* uiEntity);
            void deregisterAllUIEntities();
            std::vector<sge::UIEntity*> getAllUIEntities();

            void showUIEntity(sge::UIEntity* uiEntity);
            void hideUIEntity(sge::UIEntity* uiEntity);

        private:
            std::vector<sge::UIEntity*> m_uiEntities;

            sge::UISpriteManager* m_uiSpriteManager;
            sge::ClickableShapeManager* m_clickableShapeManager;
            sge::SpriteTextManager* m_spriteTextManager;
            sge::UIAnimationManager* m_uiAnimationManager;
    };
}

#endif

#ifndef UI_ANIMATION_MANAGER_H
#define UI_ANIMATION_MANAGER_H

#include <vector>

namespace sge{
    class Animation;

    class UIAnimationManager{
        public:
            void registerAnimation(sge::Animation* animation);
            void deregisterAnimation(sge::Animation* animation);
            std::vector<sge::Animation*> getAllActiveAnimations();

            void activateAnimation(sge::Animation* animation);
            void deactivateAnimation(sge::Animation* animation);

            void updateActiveAnimations();

        private:
            std::vector<sge::Animation*> m_activeAnimations;
            std::vector<sge::Animation*> m_inactiveAnimations;
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

    m_deltaClock.restart();

    while(m_windowPtr->isOpen()){
        sf::Time deltaTime = m_deltaClock.restart();
        float dt = deltaTime.asSeconds();
        if(dt > 0.15f) dt = 0.15f;

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
sf::Texture* sge::TextureSheet::getTexture(){ return &m_textureSheet; }
sf::IntRect sge::TextureSheet::getTextureRect(int textureN){ return m_textureRects[textureN]; }


void sge::ControllerManager::registerController(std::function<void(sf::Event)> controller){ m_controllers.push_back(controller); }
std::vector<std::function<void(sf::Event)>> sge::ControllerManager::getAllControllers(){ return m_controllers; }

void sge::ControllerManager::updateControllers(sf::Event event){
    for(std::function<void(sf::Event)> controller : m_controllers){
        controller(event);
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


sge::ClickableShape::ClickableShape(sge::UIEntity* ownerUIEntity){ m_ownerUIEntityPtr = ownerUIEntity; }

sge::UIEntity* sge::ClickableShape::getOwnerUIEntity(){ return m_ownerUIEntityPtr; }
void sge::ClickableShape::align(){ this->setPosition(m_ownerUIEntityPtr->sprite->getPosition() + offset); }
#include <algorithm>

void sge::ClickableShapeManager::registerClickableShape(sge::ClickableShape* clickableShape){ m_activeClickableShapes.push_back(clickableShape); }
void sge::ClickableShapeManager::deregsiterClickableShape(sge::ClickableShape* clickableShape){
    m_activeClickableShapes.erase(std::remove(m_activeClickableShapes.begin(), m_activeClickableShapes.end(), clickableShape), m_activeClickableShapes.end());
    m_inactiveClickableShapes.erase(std::remove(m_inactiveClickableShapes.begin(), m_inactiveClickableShapes.end(), clickableShape), m_inactiveClickableShapes.end());
}
std::vector<sge::ClickableShape*> sge::ClickableShapeManager::getAllActiveClickableShapes(){ return m_activeClickableShapes; }

void sge::ClickableShapeManager::activateClickableShape(sge::ClickableShape* clickableShape){
    deregsiterClickableShape(clickableShape);
    m_activeClickableShapes.push_back(clickableShape);
}
void sge::ClickableShapeManager::deactivateClickableShape(sge::ClickableShape* clickableShape){
    deregsiterClickableShape(clickableShape);
    m_inactiveClickableShapes.push_back(clickableShape);
}

void sge::ClickableShapeManager::alignClickableShapes(){
    for(sge::ClickableShape* clickableShape : m_activeClickableShapes){
        clickableShape->align();
    }
}


bool sge::isMouseOverClickableShape(ClickableShape* clickableShape, sf::RenderWindow* window){
    return clickableShape->getOwnerUIEntity()->sprite->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
}


void sge::SpriteManager::registerSprite(sf::Sprite* sprite){ m_sprites.push_back(sprite); }
void sge::SpriteManager::deregisterSprite(sf::Sprite* sprite){ m_sprites.erase(std::remove(m_sprites.begin(), m_sprites.end(), sprite), m_sprites.end()); }
void sge::SpriteManager::deregisterAllSprites(){ m_sprites.clear(); }
std::vector<sf::Sprite*> sge::SpriteManager::getSprites(){ return m_sprites; }


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


void sge::AnimationManager::registerAnimation(sge::Animation* animation){ m_animations.push_back(animation); }
void sge::AnimationManager::deregisterAnimation(sge::Animation* animation){ m_animations.erase(std::remove(m_animations.begin(), m_animations.end(), animation), m_animations.end()); }
void sge::AnimationManager::deregisterAllAnimations(){ m_animations.clear(); }

void sge::AnimationManager::updateAnimations(){
    for(sge::Animation* animation : m_animations){
        animation->runForward();
    }
}


sge::EntityManager::EntityManager(sge::SpriteManager* spriteManager, sge::PhysicsManager* physicsManager, sge::CollisionShapeManager* collisionShapeManager, sge::AnimationManager* animationManager, sge::CollisionManager* collisionManager){
    m_spriteManagerPtr = spriteManager;
    m_physicsManagerPtr = physicsManager;
    m_collisionShapeManager = collisionShapeManager;
    m_animationManagerPtr = animationManager;
    m_collisionManager = collisionManager;
}

void sge::EntityManager::registerEntity(sge::Entity* entity){
    m_spriteManagerPtr->registerSprite(entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->registerPhysicalObject(entity->physicalObject);
    }
        
    if(entity->collisionShapes.size()){
        for(auto& [_, collisionShape] : entity->collisionShapes){
            m_collisionShapeManager->registerCollisionShape(collisionShape);
        }
    }
    
    if(entity->animation){
        m_animationManagerPtr->registerAnimation(entity->animation);
    }

    m_entities.push_back(entity);
}

void sge::EntityManager::registerEntities(std::vector<sge::Entity*> entities){
    for(sge::Entity* entity : entities){
        registerEntity(entity);
    }
}

void sge::EntityManager::deregisterEntity(sge::Entity* entity){
    m_deregisterEntityFromCoreManagers(entity);

    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());    
}

void sge::EntityManager::deregisterAllEntities(){
    for(Entity* entity : m_entities){
        m_deregisterEntityFromCoreManagers(entity);
    }

    m_entities.clear();
}

std::vector<sge::Entity*> sge::EntityManager::getAllEntities(){ return m_entities; }

void sge::EntityManager::m_deregisterEntityFromCoreManagers(sge::Entity* entity){
    m_spriteManagerPtr->deregisterSprite(entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->deregisterPhysicalObject(entity->physicalObject);
    }

    if(entity->collisionShapes.size()){
        for(auto[_, collisionShape] : entity->collisionShapes){
            m_collisionShapeManager->deregisterCollisionShape(collisionShape);
            m_collisionManager->deregisterCollisionShapeFromCollisionGroups(collisionShape);
        }
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
void sge::DebugManager::registerDebugEntities(std::vector<sge::DebugEntity*> debugEntities){
    for(DebugEntity* debugEntity : debugEntities){
        registerDebugEntity(debugEntity);
    }
}
void sge::DebugManager::deregisterDebugEntity(sge::DebugEntity* debugEntity){ m_debugEntities.erase(std::remove(m_debugEntities.begin(), m_debugEntities.end(), debugEntity), m_debugEntities.end()); }
void sge::DebugManager::deregisterAllDebugEntities(){ m_debugEntities.clear(); }

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


void sge::Scene::registerEntity(sge::Entity* entity){ m_entities.push_back(entity); }
void sge::Scene::registerEntities(std::vector<sge::Entity*> entities){
    for(Entity* entity : entities){
        registerEntity(entity);
    }
}
void sge::Scene::registerDebugEntity(sge::DebugEntity* debugEntity){ m_debugEntities.push_back(debugEntity); }
void sge::Scene::registerDebugEntities(std::vector<DebugEntity*> debugEntities){
    for(DebugEntity* debugEntity : debugEntities){
        registerDebugEntity(debugEntity);
    }
}
void sge::Scene::registerCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionShapes){ m_collisionGroups[name] = collisionShapes; }
void sge::Scene::registerCollisionPair(std::string name, sge::CollisionPair* collisionPair){
    m_collisionPairs[name] = collisionPair;
    m_collisionPairsOrder.push_back(name);
}

std::vector<sge::Entity*> sge::Scene::getEntities(){ return m_entities; }
std::vector<sge::DebugEntity*> sge::Scene::getDebugEntities(){ return m_debugEntities; }
std::unordered_map<std::string, std::vector<sge::CollisionShape*>> sge::Scene::getCollisionGroups(){ return m_collisionGroups; };
std::unordered_map<std::string, sge::CollisionPair*> sge::Scene::getCollisionPairs(){ return m_collisionPairs; }
std::vector<std::string> sge::Scene::getCollisionPairsOrder(){ return m_collisionPairsOrder; };


sge::SceneManager::SceneManager(
        sge::SpriteManager* spriteManager,
        sge::PhysicsManager* physicsManager,
        sge::CollisionShapeManager* collisionShapeManager,
        sge::AnimationManager* animationManager,
        sge::CollisionManager* collisionManager,
        sge::EntityManager* entityManager,
        sge::DebugManager* debugManager
    ){
    
    
    m_spriteManagerPtr = spriteManager;
    m_physicsManagerPtr = physicsManager;
    m_collisionShapeManagerPtr = collisionShapeManager;
    m_animationManagerPtr = animationManager;
    m_collisionManagerPtr = collisionManager;
    m_entityManagerPtr = entityManager;
    m_debugManagerPtr = debugManager;
}

void sge::SceneManager::registerScene(std::string name, sge::Scene* scene){ m_scenes[name] = scene; }
void sge::SceneManager::setCurrentScene(std::string name){ m_currentScene = name; }
void sge::SceneManager::alignScene(){
    if(m_currentScene.length()){
        if(m_loadedScene != m_currentScene){
            m_entityManagerPtr->deregisterAllEntities();
            m_spriteManagerPtr->deregisterAllSprites();
            m_physicsManagerPtr->deregisterAllPhysicalObjects();
            m_collisionShapeManagerPtr->deregisterAllCollisionShapes();
            m_collisionManagerPtr->deregisterAllCollisionGroups();
            m_collisionManagerPtr->deregisterAllCollisionPairs();
            m_animationManagerPtr->deregisterAllAnimations();
            m_debugManagerPtr->deregisterAllDebugEntities();

            m_entityManagerPtr->registerEntities(m_scenes[m_currentScene]->getEntities());
            m_debugManagerPtr->registerDebugEntities(m_scenes[m_currentScene]->getDebugEntities());
            m_collisionManagerPtr->registerCollisionGroups(m_scenes[m_currentScene]->getCollisionGroups());
            m_collisionManagerPtr->registerCollisionPairs(m_scenes[m_currentScene]->getCollisionPairs());
            m_collisionManagerPtr->setCollisionPairsOrder(m_scenes[m_currentScene]->getCollisionPairsOrder());

            m_loadedScene = m_currentScene;
        }
    }
}


void sge::UISpriteManager::registerSprite(sf::Sprite* sprite){ m_visibleSprites.push_back(sprite); }
void sge::UISpriteManager::deregisterSprite(sf::Sprite* sprite){
    m_visibleSprites.erase(std::remove(m_visibleSprites.begin(), m_visibleSprites.end(), sprite), m_visibleSprites.end());
    m_hiddenSprites.erase(std::remove(m_hiddenSprites.begin(), m_hiddenSprites.end(), sprite), m_hiddenSprites.end());

}
std::vector<sf::Sprite*> sge::UISpriteManager::getAllVisibleSprites(){ return m_visibleSprites; }

void sge::UISpriteManager::showSprite(sf::Sprite* sprite){
    deregisterSprite(sprite);
    m_visibleSprites.push_back(sprite);
}
void sge::UISpriteManager::hideSprite(sf::Sprite* sprite){
    deregisterSprite(sprite);
    m_hiddenSprites.push_back(sprite);
}


sge::SpriteText::SpriteText(sf::Sprite* ownerSprite){ m_ownerSpritePtr = ownerSprite; }
void sge::SpriteText::align(){
    sf::Vector2f pos = m_ownerSpritePtr->getPosition() + offset; 
    
    this->setPosition((int)pos.x, (int)pos.y);
}
#include <algorithm>

void sge::SpriteTextManager::registerSpriteText(sge::SpriteText* spriteText){ m_visibleSpriteTextObjects.push_back(spriteText); }
void sge::SpriteTextManager::deregisterSpriteText(sge::SpriteText* spriteText){
    m_visibleSpriteTextObjects.erase(std::remove(m_visibleSpriteTextObjects.begin(), m_visibleSpriteTextObjects.end(), spriteText), m_visibleSpriteTextObjects.end());
    m_hiddenSpriteTextObjects.erase(std::remove(m_hiddenSpriteTextObjects.begin(), m_hiddenSpriteTextObjects.end(), spriteText), m_hiddenSpriteTextObjects.end());
}
std::vector<sge::SpriteText*> sge::SpriteTextManager::getAllVisibleSpriteTextObjects(){ return m_visibleSpriteTextObjects; }

void sge::SpriteTextManager::showSpriteText(sge::SpriteText* spriteText){
    deregisterSpriteText(spriteText);
    m_visibleSpriteTextObjects.push_back(spriteText);
}
void sge::SpriteTextManager::hideSpriteText(sge::SpriteText* spriteText){
    deregisterSpriteText(spriteText);
    m_hiddenSpriteTextObjects.push_back(spriteText);
}

void sge::SpriteTextManager::alignSpriteTextObjects(){
    for(sge::SpriteText* spriteText : m_visibleSpriteTextObjects){
        spriteText->align();
    }
}


sge::UIEntityManager::UIEntityManager(sge::UISpriteManager* uiSpriteManager, sge::ClickableShapeManager* clickableShapeManager, sge::SpriteTextManager* spriteTextManager, sge::UIAnimationManager* uiAnimationManager){
    m_uiSpriteManager = uiSpriteManager;
    m_clickableShapeManager = clickableShapeManager;
    m_spriteTextManager = spriteTextManager;
    m_uiAnimationManager = uiAnimationManager;
}

void sge::UIEntityManager::registerUIEntity(sge::UIEntity* uiEntity){
    m_uiSpriteManager->registerSprite(uiEntity->sprite);

    if(uiEntity->clickableShape){
        m_clickableShapeManager->registerClickableShape(uiEntity->clickableShape);
    }

    if(uiEntity->spriteText){
        m_spriteTextManager->registerSpriteText(uiEntity->spriteText);
    }

    if(uiEntity->animation){
        m_uiAnimationManager->registerAnimation(uiEntity->animation);
    }

    m_uiEntities.push_back(uiEntity);
}
void sge::UIEntityManager::deregisterUIEntity(sge::UIEntity* uiEntity){
    m_uiSpriteManager->deregisterSprite(uiEntity->sprite);

    if(uiEntity->clickableShape){
        m_clickableShapeManager->deregsiterClickableShape(uiEntity->clickableShape);
    }

    if(uiEntity->spriteText){
        m_spriteTextManager->deregisterSpriteText(uiEntity->spriteText);
    }

    if(uiEntity->animation){
        m_uiAnimationManager->deregisterAnimation(uiEntity->animation);
    }

    m_uiEntities.erase(std::remove(m_uiEntities.begin(), m_uiEntities.end(), uiEntity), m_uiEntities.end());
}
void sge::UIEntityManager::deregisterAllUIEntities(){
    for(sge::UIEntity* uiEntity : m_uiEntities){
        deregisterUIEntity(uiEntity);
    }
}
std::vector<sge::UIEntity*> sge::UIEntityManager::getAllUIEntities(){ return m_uiEntities; }

void sge::UIEntityManager::showUIEntity(sge::UIEntity* uiEntity){
    m_uiSpriteManager->showSprite(uiEntity->sprite);

    if(uiEntity->clickableShape){
        m_clickableShapeManager->activateClickableShape(uiEntity->clickableShape);
    }

    if(uiEntity->spriteText){
        m_spriteTextManager->showSpriteText(uiEntity->spriteText);
    }

    if(uiEntity->animation){
        m_uiAnimationManager->activateAnimation(uiEntity->animation);
    }
}
void sge::UIEntityManager::hideUIEntity(sge::UIEntity* uiEntity){
    m_uiSpriteManager->hideSprite(uiEntity->sprite);

    if(uiEntity->clickableShape){
        m_clickableShapeManager->deactivateClickableShape(uiEntity->clickableShape);
    }

    if(uiEntity->spriteText){
        m_spriteTextManager->hideSpriteText(uiEntity->spriteText);
    }

    if(uiEntity->animation){
        m_uiAnimationManager->deactivateAnimation(uiEntity->animation);
    }
}
#include <algorithm>

void sge::UIAnimationManager::registerAnimation(sge::Animation* animation){ m_activeAnimations.push_back(animation); }
void sge::UIAnimationManager::deregisterAnimation(sge::Animation* animation){
    m_activeAnimations.erase(std::remove(m_activeAnimations.begin(), m_activeAnimations.end(), animation), m_activeAnimations.end());
    m_inactiveAnimations.erase(std::remove(m_inactiveAnimations.begin(), m_inactiveAnimations.end(), animation), m_inactiveAnimations.end());
}
std::vector<sge::Animation*> sge::UIAnimationManager::getAllActiveAnimations(){ return m_activeAnimations; }

void sge::UIAnimationManager::activateAnimation(sge::Animation* animation){
    deregisterAnimation(animation);
    m_activeAnimations.push_back(animation);
}
void sge::UIAnimationManager::deactivateAnimation(sge::Animation* animation){
    deregisterAnimation(animation);
    m_inactiveAnimations.push_back(animation);
}

void sge::UIAnimationManager::updateActiveAnimations(){
    for(sge::Animation* animation : m_activeAnimations){
        animation->runForward();
    }
}


#endif