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
    class StateManager;
    class CollisionManager;
    class EntityManager;
    class SceneManager;
    

    class Universe{
        public:
            Universe(sf::RenderWindow* window);

            bool isPaused = false;
            float dtCap = .15f;

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
            sge::StateManager* m_stateManager = nullptr;

            sge::ClickableShapeManager* m_clickableShapeManager = nullptr;
            sge::SpriteTextManager* m_spriteTextManager = nullptr;
    };
}

#endif

// Manager
#ifndef VECTOR_MANAGER_H
#define VECTOR_MANAGER_H

#include <algorithm>
#include <vector>

namespace sge{
    template<typename T>
    class VectorManager{
        public:
            void registerComponent(T component){ m_components.push_back(component); }
            void deregisterComponent(T component){ m_components.erase(std::remove(m_components.begin(), m_components.end(), component), m_components.end()); }
            std::vector<T> getComponents(){ return m_components; };
        
        protected:
            std::vector<T> m_components;
    };
}

#endif
#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <unordered_map>
#include <vector>

namespace sge{
    template<typename T>
    class ViewManager{
        public:
            void registerComponent(sf::View* view, T component){ m_components[view].push_back(component); }
            void deregisterComponent(sf::View* view, T component){ m_components[view].erase(std::remove(m_components[view].begin(), m_components[view].end(), component), m_components[view].end()); }
            std::vector<T> getViewComponents(sf::View* view){ return m_components[view]; }
            std::unordered_map<sf::View*, std::vector<T>> getComponentsUnorderedMap(){ return m_components; }

        protected:
            std::unordered_map<sf::View*, std::vector<T>> m_components;
    };
}

#endif
#ifndef LABEL_MANAGER_H
#define LABEL_MANAGER_H

#include <string>
#include <unordered_map>

namespace sge{
    template<typename T>
    class LabelManager{
        public:
            void registerComponent(std::string label, T component){ m_components[label] = component; }
            void deregisterComponent(std::string label){ m_components.erase(label); }
            T getComponent(std::string label){ return m_components[label]; }
            std::unordered_map<std::string, T> getComponentsMap(){ return m_components; }

        protected:
            std::unordered_map<std::string, T> m_components;
    };
}

#endif
//

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

#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <SFML/Graphics.hpp>

namespace sge{
    struct DrawManager{
        virtual void draw(sf::RenderWindow* window){};
    };
}

#endif

namespace sge{
    class DebugEntity;

    class DebugManager :
        public sge::ViewManager<sge::DebugEntity*>,
        public sge::DrawManager{

        public:
            void draw(sf::RenderWindow* window) override;
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

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <SFML/Graphics.hpp>

namespace sge{
    struct EventManager{
        virtual void processEvent(sf::Event event){};
    };
}

#endif

namespace sge{
    class ControllerManager :
        public sge::VectorManager<std::function<void(sf::Event)>>,
        public sge::EventManager{

        public:
            void processEvent(sf::Event event) override;
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

#ifndef UPDATE_MANAGER_H
#define UPDATE_MANAGER_H

namespace sge{
    struct UpdateManager{
        virtual void update(float dt){};
    };
}

#endif

namespace sge{
    struct ScriptedView;

    class ScriptedViewManager :
        public sge::VectorManager<sge::ScriptedView*>,
        public sge::UpdateManager{

        public:
            void update(float dt) override;
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
    class SpriteManager :
        public sge::ViewManager<sf::Sprite*>,
        public sge::DrawManager{
            
        public:
            void draw(sf::RenderWindow* window) override;
    };
}

#endif

#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include <vector>

namespace sge{
    class PhysicalObject;

    class PhysicsManager :
        public sge::VectorManager<sge::PhysicalObject*>,
        public sge::UpdateManager{

        public:
            void update(float dt) override;
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

    class CollisionShapeManager :
        public sge::VectorManager<sge::CollisionShape*>,
        public sge::UpdateManager{

        public:
            void update(float dt) override;
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

    class ClickableShapeManager :
        public sge::ViewManager<ClickableShape*>,
        public sge::UpdateManager,
        public sge::EventManager{

        public:
            void update(float dt) override;
            void processEvent(sf::Event event) override;
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

    class SpriteTextManager :
        public sge::ViewManager<sge::SpriteText*>,
        public sge::UpdateManager,
        public sge::DrawManager{
            
        public:
            void update(float dt) override;
            void draw(sf::RenderWindow* window) override;
    };  
}

#endif

#include <vector>

namespace sge{
    class Animation;

    class AnimationManager :
        public sge::VectorManager<sge::Animation*>,
        public sge::UpdateManager{
        
        public:
            void update(float dt) override;
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

#ifndef STATE_H
#define STATE_H

#include <functional>

namespace sge{
    class StateCluster;
    struct Entity;

    class State{
        public:
            State(Entity* ownerEntity);

            virtual void enterScript(){}
            virtual void exitScript(){}
            virtual void updateScript(float dt, sge::StateCluster* containerStateCluster){}

        protected:
            Entity* m_ownerEntityPtr;
    };
}

#endif
#ifndef STATE_CLUSTER_H
#define STATE_CLUSTER_H

#include <unordered_map>
#include <functional>
#include <string>

namespace sge{
    struct State;

    class StateCluster{
        public:
            sge::State* getCurrentState();
            std::string getCurrentStateName();
            void setCurrentState(std::string name);

            std::unordered_map<std::string, sge::State*> states;
            
        private:
            std::string m_currentState = "";
    };
}

#endif
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <vector>

namespace sge{
    class StateCluster;

    class StateManager :
        public sge::VectorManager<sge::StateCluster*>,
        public sge::UpdateManager{

        public:
            void update(float dt) override;
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
    class StateCluster;

    struct Entity{
        sf::Sprite* sprite;
        sge::PhysicalObject* physicalObject = nullptr;
        std::unordered_map<std::string, sge::CollisionShape*> collisionShapes; 
        sge::ClickableShape* clickableShape = nullptr;
        sge::SpriteText* spriteText = nullptr;
        sge::Animation* animation = nullptr;
        sge::StateCluster* stateCluster = nullptr;
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
    class StateManager;

    class EntityManager : public sge::ViewManager<sge::Entity*>{
        public:
            EntityManager(
                sge::SpriteManager* spriteManager,
                sge::PhysicsManager* physicsManager,
                sge::CollisionShapeManager* collisionShapeManager,
                sge::ClickableShapeManager* clickableShapeManager,
                sge::SpriteTextManager* SpriteTextManager,
                sge::AnimationManager* animationManager,
                sge::StateManager* stateManager,
                sge::CollisionManager* collisionManager
            );

        void registerEntity(sf::View* view, sge::Entity* entity);
        void deregisterEntity(sf::View* view, sge::Entity* entity);

        private:
            // Hidden because extended using 'registerEntiy' and 'deregisterEntity'
            using sge::ViewManager<sge::Entity*>::registerComponent;
            using sge::ViewManager<sge::Entity*>::deregisterComponent;
            //

            sge::SpriteManager* m_spriteManagerPtr;
            sge::PhysicsManager* m_physicsManagerPtr;
            sge::CollisionShapeManager* m_collisionShapeManagerPtr;
            sge::ClickableShapeManager* m_clickableShapeManagerPtr;
            sge::SpriteTextManager* m_spriteTextManagerPtr;
            sge::AnimationManager* m_animationManagerPtr;
            sge::StateManager* m_stateManagerPtr;
            sge::CollisionManager* m_collisionManagerPtr;
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

    class SceneManager : public sge::LabelManager<sge::Scene*>{
        public:
            SceneManager(sge::EntityManager* entityManager, sge::CollisionManager* collisionManager);
            void setupDebug(sge::DebugManager* debugManager);

            void setCurrentScene(std::string name);
            void alignScene();
        
        private:
            sge::EntityManager* m_entityManagerPtr = nullptr;
            sge::CollisionManager* m_collisionManagerPtr = nullptr;
            sge::DebugManager* m_debugManagerPtr = nullptr;

            std::string m_currentScene = "";
            std::string m_loadedScene = "";
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
    sge::StateManager* StM = new sge::StateManager();
    sge::CollisionManager* CM = new sge::CollisionManager();
    sge::EntityManager* EM = new sge::EntityManager(SpM, PM, CSM, ClSM, STM, AnM, StM, CM);
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
    m_stateManager = StM;
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
    m_deltaClock.restart();

    while(m_windowPtr->isOpen()){
        sf::Time deltaTime = m_deltaClock.restart();
        float dt = deltaTime.asSeconds();
        if(dt > dtCap) dt = dtCap;

        sf::Event event;
        while(m_windowPtr->pollEvent(event)){
            if(event.type == sf::Event::Closed) m_windowPtr->close();

            controllerManager->processEvent(event);
            m_clickableShapeManager->processEvent(event);
        }

        if(!isPaused){
            m_physicsManager->update(dt);
            m_collisionShapeManager->update(dt);
            m_clickableShapeManager->update(dt);
            m_spriteTextManager->update(dt);
            m_stateManager->update(dt);
            collisionManager->updateCollisions();

            m_animationManager->update(dt);
            scriptedViewManager->update(dt);

            sceneManager->alignScene(); // Scene can be reset only after all managers finished their updates to prevent segfaults in loops
        }
        
        
        m_windowPtr->clear();
        
        m_spriteManager->draw(m_windowPtr);
        m_spriteTextManager->draw(m_windowPtr);
        if(debugManager) debugManager->draw(m_windowPtr);

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


void sge::DebugManager::draw(sf::RenderWindow* window){
    for(auto& [view, debugEntities]: m_components){
        window->setView(*view);
        
        for(sge::DebugEntity* debugEntity : debugEntities){
            // Run extraDebugFunctions
            // ! rewrite into update or just remove
            for(std::function<void(sf::RenderWindow* renderWindow)> extraDebugFunction : debugEntity->getExtraDebugFunctions()){
                extraDebugFunction(window);
            }
            //

            // Draw collision shape borders
            if(debugEntity->drawCollisionShapeBorders){
                for(sge::CollisionShapeBorder* collisionShapeBorder : debugEntity->generateCollisionShapeBorders()){
                    window->draw(*collisionShapeBorder);
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


void sge::ControllerManager::processEvent(sf::Event event){
    for(std::function<void(sf::Event)> controller : m_components){
        controller(event);
    }
}


void sge::ScriptedViewManager::update(float dt){
    for(sge::ScriptedView* scriptedView : m_components){
        if(scriptedView->script){
            scriptedView->script(scriptedView);
        }
    }
}


void sge::SpriteManager::draw(sf::RenderWindow* window){
    for(auto [view, sprites] : m_components){
        window->setView(*view);

        for(sf::Sprite* sprite : sprites){
            window->draw(*sprite);
        }
    }
}


void sge::PhysicsManager::update(float dt){
    for(sge::PhysicalObject* physicalObject : m_components){
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

void sge::CollisionShapeManager::update(float dt){
    for(sge::CollisionShape* collisionShape : m_components){
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

void sge::ClickableShapeManager::update(float dt){
    for(auto& [_, clickableShapes] : m_components){
        for(sge::ClickableShape* clickableShape : clickableShapes){
            clickableShape->align();
        }
    }
}

void sge::ClickableShapeManager::processEvent(sf::Event event){
    for(auto& [_, clickableShapes] : m_components){
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

void sge::SpriteTextManager::update(float dt){
    for(auto& [_, spriteTextObjects] : m_components){
        for(sge::SpriteText* spriteText : spriteTextObjects){
            spriteText->align();
        }
    }
}
void sge::SpriteTextManager::draw(sf::RenderWindow* window){
    for(auto& [view, spriteTextObjects] : m_components){
        window->setView(*view);

        for(SpriteText* spriteText : spriteTextObjects){
            window->draw(*spriteText);
        }
    }
}


void sge::AnimationManager::update(float dt){
    for(sge::Animation* animation : m_components){
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


sge::State::State(Entity* ownerEntity){ m_ownerEntityPtr = ownerEntity; }


sge::State* sge::StateCluster::getCurrentState(){ return states[m_currentState]; }
std::string sge::StateCluster::getCurrentStateName(){ return m_currentState; }
void sge::StateCluster::setCurrentState(std::string name){
    if(m_currentState != ""){
        states[m_currentState]->exitScript();
    }
    states[name]->enterScript();

    m_currentState = name;
}
#include <algorithm>

void sge::StateManager::update(float dt){
    for(StateCluster* stateCluster : m_components){
        stateCluster->getCurrentState()->updateScript(dt, stateCluster);
    }
}


sge::EntityManager::EntityManager(
        sge::SpriteManager* spriteManager,
        sge::PhysicsManager* physicsManager,
        sge::CollisionShapeManager* collisionShapeManager,
        sge::ClickableShapeManager* clickableShapeManager,
        sge::SpriteTextManager* spriteTextManager,
        sge::AnimationManager* animationManager,
        sge::StateManager* stateManager,
        sge::CollisionManager* collisionManager
    ){

    m_spriteManagerPtr = spriteManager;
    m_physicsManagerPtr = physicsManager;
    m_collisionShapeManagerPtr = collisionShapeManager;
    m_clickableShapeManagerPtr = clickableShapeManager;
    m_spriteTextManagerPtr = spriteTextManager;
    m_animationManagerPtr = animationManager;
    m_stateManagerPtr = stateManager;
    m_collisionManagerPtr = collisionManager;
}

void sge::EntityManager::registerEntity(sf::View* view, sge::Entity* entity){
    m_spriteManagerPtr->registerComponent(view, entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->registerComponent(entity->physicalObject);
    }
        
    if(entity->collisionShapes.size()){
        for(auto& [_, collisionShape] : entity->collisionShapes){
            m_collisionShapeManagerPtr->registerComponent(collisionShape);
        }
    }

    if(entity->clickableShape){
        m_clickableShapeManagerPtr->registerComponent(view, entity->clickableShape);
    }

    if(entity->spriteText){
        m_spriteTextManagerPtr->registerComponent(view, entity->spriteText);
    }
    
    if(entity->animation){
        m_animationManagerPtr->registerComponent(entity->animation);
    }

    if(entity->stateCluster){
        m_stateManagerPtr->registerComponent(entity->stateCluster);
    }

    sge::ViewManager<sge::Entity*>::registerComponent(view, entity);
}

void sge::EntityManager::deregisterEntity(sf::View* view, sge::Entity* entity){
    m_spriteManagerPtr->deregisterComponent(view, entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->deregisterComponent(entity->physicalObject);
    }

    if(entity->collisionShapes.size()){
        for(auto[_, collisionShape] : entity->collisionShapes){
            m_collisionShapeManagerPtr->deregisterComponent(collisionShape);
            m_collisionManagerPtr->deregisterCollisionShapeFromCollisionGroups(collisionShape);
        }
    }

    if(entity->clickableShape){
        m_clickableShapeManagerPtr->deregisterComponent(view, entity->clickableShape);
    }

    if(entity->spriteText){
        m_spriteTextManagerPtr->deregisterComponent(view, entity->spriteText);
    }

    if(entity->animation){
        m_animationManagerPtr->deregisterComponent(entity->animation);
    }

    if(entity->stateCluster){
        m_stateManagerPtr->deregisterComponent(entity->stateCluster);
    }

    sge::ViewManager<sge::Entity*>::deregisterComponent(view, entity);
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

void sge::SceneManager::setCurrentScene(std::string name){ m_currentScene = name; }
void sge::SceneManager::alignScene(){
    if(m_currentScene.length()){
        if(m_loadedScene != m_currentScene){
            // Reset previous scene members
            if(m_debugManagerPtr){
                for(auto& [view, debugEntities] : m_components[m_loadedScene]->getDebugEntitiesMap()){
                    for(sge::DebugEntity* debugEntity : debugEntities){
                        m_debugManagerPtr->deregisterComponent(view, debugEntity);
                    }
                }
            }

            for(auto& [view, entities] : m_components[m_loadedScene]->getEntitiesMap()){
                for(sge::Entity* entity : entities){
                    m_entityManagerPtr->deregisterEntity(view, entity);
                }
            }

            for(auto& [name, _] : m_components[m_loadedScene]->getCollisionGroups()){
                m_collisionManagerPtr->deregisterCollisionGroup(name);
            }
            // * Collision pairs and order gets auto removed
            //

            // Register new scene members
            for(auto& [view, entities] : m_components[m_currentScene]->getEntitiesMap()){
                for(sge::Entity* entity : entities){
                    m_entityManagerPtr->registerEntity(view, entity);
                }
            }

            if(m_debugManagerPtr){
                for(auto& [view, debugEntities] : m_components[m_currentScene]->getDebugEntitiesMap()){
                    for(sge::DebugEntity* debugEntity : debugEntities){
                        m_debugManagerPtr->registerComponent(view, debugEntity);
                    }
                }
            }
    
            m_collisionManagerPtr->registerCollisionGroups(m_components[m_currentScene]->getCollisionGroups());
            m_collisionManagerPtr->registerCollisionPairs(m_components[m_currentScene]->getCollisionPairs());
            m_collisionManagerPtr->setCollisionPairsOrder(m_components[m_currentScene]->getCollisionPairsOrder());
            //

            m_loadedScene = m_currentScene;
        }
    }
}


#endif