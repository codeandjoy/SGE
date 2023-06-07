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
    class DrumSceneManager;
    class LayerSceneManager;
    

    class Universe{
        public:
            Universe(sf::RenderWindow* window);

            float dtCap = .15f;

            void setupDebug();
            void loop();

            sge::AssetsManager* assetsManager = nullptr;
            sge::ControllerManager* controllerManager = nullptr;
            sge::DebugManager* debugManager = nullptr;
            sge::ScriptedViewManager* scriptedViewManager = nullptr;

            sge::CollisionManager* collisionManager = nullptr;
            sge::EntityManager* entityManager = nullptr;
            sge::DrumSceneManager* drumSceneManager = nullptr;
            sge::LayerSceneManager* layerSceneManager = nullptr;

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

// Component
#ifndef STATEFUL_COMPONENT_H
#define STATEFUL_COMPONENT_H

namespace sge{
    struct StatefulComponent{
        bool isActive = true;
        bool isPaused = false;
        bool isHidden = false;

        void activate(){
            isActive = true;
            isPaused = false;
            isHidden = false;
        }
        void pause(){
            isActive = false;
            isPaused = true;
            isHidden = false;
        }
        void hide(){
            isActive = false;
            isPaused = false;
            isHidden = true;
        }
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

    // TODO return nulls when asset does not exist
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
            sf::IntRect getTextureRect(int textureN, bool isFlippedHorizontally, bool isFlippedVertically);

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

    class DebugEntity : public sge::StatefulComponent{
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
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>

namespace sge{
    class Controller{
        public: 
            virtual void script(sf::Event event){};
    };
}

#endif
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
    class Controller;

    class ControllerManager :
        public sge::VectorManager<sge::Controller*>,
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
        virtual void script(){};
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
    class Sprite;

    class SpriteManager :
        public sge::ViewManager<sge::Sprite*>,
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
    class PhysicalObject : public sge::StatefulComponent{
        public:
            PhysicalObject(sf::Sprite* ownerSprite);

            sf::Sprite* getOwnerSprite();

            sf::Vector2f velocity = sf::Vector2f(0, 0);
            sf::Vector2f acceleration = sf::Vector2f(0, 0);

            void createContinuousComputation(std::string name, std::function<void(sge::PhysicalObject*, float)> computation);

            void update(float dt);

        private:
            sf::Sprite* m_ownerSpritePtr;

            std::unordered_map<std::string, std::function<void(sge::PhysicalObject*, float)>> m_continuousComputations;
            std::vector<std::string> m_continuousComputationOrder;
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
    class CollisionShape;
    class CollisionInteraction;
    class CollisionShapeManager;

    class CollisionManager : public sge::VectorManager<CollisionInteraction*>{
        public:
            CollisionManager(CollisionShapeManager* collisionShapeManager): m_collisionShapeManagerPtr(collisionShapeManager){};

            void updateCollisions();

        private:
            CollisionShapeManager* m_collisionShapeManagerPtr;
    };
}

#endif
#ifndef COLLISION_INTERACTION_H
#define COLLISION_INTERACTION_H

#include <unordered_map>
#include <vector>
#include <string>

namespace sge{
    struct Collision;
    class CollisionShape;
    class CollisionManager;

    class CollisionInteraction{
        friend class CollisionManager;
        
        public:
            CollisionInteraction(std::vector<std::string> initiatorGroups, std::vector<std::string> recipientGroups)
                : initiatorGroups(initiatorGroups), recipientGroups(recipientGroups){};

            std::vector<std::string> initiatorGroups = {};
            std::vector<std::string> recipientGroups = {};

            virtual bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient){ return false; }

            virtual void startPhaseCollisionResponse(std::vector<sge::Collision> collisions){}
            virtual void continuousPhaseCollisionResponse(std::vector<sge::Collision> collisions){}
            virtual void endPhaseCollisionResponse(std::vector<sge::Collision> collisions){}

        protected:
            std::unordered_map<sge::CollisionShape*, std::vector<sge::Collision>> pastCollisions;
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
#include <vector>
#include <string>

namespace sge{
    class Entity;
    struct Measurements;

    class CollisionShape : public sge::StatefulComponent, public sf::RectangleShape{
        public:
            CollisionShape(sge::Entity* ownerEntity);

            sf::Vector2f offset = sf::Vector2f(0, 0);
            std::vector<std::string> collisionGroups;

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
            std::vector<sge::CollisionShape*> getComponentsByCollisionGroup(std::string groupName);

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

    class ClickableShape : public sge::StatefulComponent, public sf::RectangleShape{
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
    class SpriteText : public sge::StatefulComponent, public sf::Text{
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

#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <vector>

namespace sge{
    class AnimationCluster;

    class AnimationManager :
        public sge::VectorManager<sge::AnimationCluster*>,
        public sge::UpdateManager{
        
        public:
            void update(float dt) override;
    };
}

#endif
#ifndef ANIMATION_CLUSTER_H
#define ANIMATION_CLUSTER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace sge{
    class TextureSequence;

    class AnimationCluster : public sge::StatefulComponent{
        public:
            AnimationCluster(sf::Sprite* ownerSprite) : m_ownerSpritePtr(ownerSprite){};
        
            int animationDelayMilliseconds = 100;
            
            void addTextureSequence(std::string name, TextureSequence* animationSequence);
            void setCurrentTextureSequence(std::string name);
        
            void run();

        private:
            sf::Sprite* m_ownerSpritePtr;
            
            std::unordered_map<std::string, TextureSequence*> m_textureSequences;
            void m_updateTexture();

            sf::Clock m_clock;
            std::string m_currentTextureSequence;
            int m_currentTextureN = 0;
    };
}

#endif
#ifndef TEXTURE_SEQUENCE_H
#define TEXTURE_SEQUENCE_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace sge{
    class TextureSheet;    

    class TextureSequence{
        public:
            TextureSequence(std::vector<int> textureSequence, sge::TextureSheet* textureSheetPtr, bool isFlippedHorizontally, bool isFlippedVertically);

            std::vector<sf::IntRect> sequenceRects;
            TextureSheet* textureSheet;
            // TODO create runForward / cycle flags and use them in 'Animation'
    };
}

#endif

#ifndef STATE_H
#define STATE_H

#include <functional>

namespace sge{
    class StateCluster;
    class Entity;

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

    class StateCluster : public sge::StatefulComponent{
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

#include <unordered_map>

namespace sge{
    class Sprite;
    class PhysicalObject;
    class CollisionShape;
    class ClickableShape;
    class SpriteText;
    class AnimationCluster;
    class StateCluster;

    class Entity : public sge::StatefulComponent{
        public:
            sge::Sprite* sprite = nullptr;
            sge::PhysicalObject* physicalObject = nullptr;
            std::unordered_map<std::string, sge::CollisionShape*> collisionShapes; 
            sge::ClickableShape* clickableShape = nullptr;
            sge::SpriteText* spriteText = nullptr;
            sge::AnimationCluster* animationCluster = nullptr;
            sge::StateCluster* stateCluster = nullptr;

            void activateEntityParts();
            void pauseEntityParts();
            void hideEntityParts();

        private:
            // Hidden because extended using 'activateEntityParts', 'pauseEntityParts' and 'hideEntityParts'
            using sge::StatefulComponent::activate;
            using sge::StatefulComponent::pause;
            using sge::StatefulComponent::hide;
            // 
    };
}

#endif
#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

namespace sge{
    class Entity;
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
                sge::StateManager* stateManager
            );

        void registerComponent(sf::View* view, sge::Entity* entity);
        void deregisterComponent(sf::View* view, sge::Entity* entity);

        private:
            // Hidden because extended
            using sge::ViewManager<sge::Entity*>::registerComponent;
            using sge::ViewManager<sge::Entity*>::deregisterComponent;
            //

            void m_registerEntityMembers(sf::View* view, sge::Entity* entity);
            void m_deregisterEntityMembers(sf::View* view, sge::Entity* entity);

            sge::SpriteManager* m_spriteManagerPtr;
            sge::PhysicsManager* m_physicsManagerPtr;
            sge::CollisionShapeManager* m_collisionShapeManagerPtr;
            sge::ClickableShapeManager* m_clickableShapeManagerPtr;
            sge::SpriteTextManager* m_spriteTextManagerPtr;
            sge::AnimationManager* m_animationManagerPtr;
            sge::StateManager* m_stateManagerPtr;
    };
}

#endif
#ifndef PLAIN_ENTITY_H
#define PLAIN_ENTITY_H

#include <SFML/Graphics.hpp>

#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/Graphics.hpp>

namespace sge{
    class Sprite : public sge::StatefulComponent, public sf::Sprite{
        public:
            Sprite() : sf::Sprite(){};
            Sprite(const sf::Texture& texture) : sf::Sprite(texture){};
            Sprite(const sf::Texture& texture, const sf::IntRect& rectangle) : sf::Sprite(texture, rectangle){};
    };
}

#endif

namespace sge{
    class PlainEntity : public sge::Entity{
        public:
            PlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
                sprite = new sge::Sprite(*texture, textureRect);
                sprite->setPosition(position);
            }
    };
}

#endif
#ifndef VOID_ENTITY_H
#define VOID_ENTITY_H

#include <SFML/Graphics.hpp>

namespace sge{
    class VoidEntity : public sge::Entity{
        public:
            VoidEntity(sf::Vector2f size, sf::Vector2f position, std::vector<std::string> collisionGroups){
                sprite = new sge::Sprite();
                sprite->setPosition(position);
                
                collisionShapes["global_bounds"] = new sge::CollisionShape(this);
                collisionShapes["global_bounds"]->setSize(size);
                collisionShapes["global_bounds"]->collisionGroups = collisionGroups;
            }
    };
}

#endif
#ifndef STATIC_ENTITY_H
#define STATIC_ENTITY_H

namespace sge{
    class StaticEntity : public sge::PlainEntity{
        public:
            StaticEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups)
                : sge::PlainEntity(texture, textureRect, position){
                    collisionShapes["global_bounds"] = new sge::CollisionShape(this);
                    collisionShapes["global_bounds"]->collisionGroups = collisionGroups;
                }
    };
}

#endif
#ifndef MOBILE_ENTITY_H
#define MOBILE_ENTITY_H

#include <SFML/Graphics.hpp>

namespace sge{
    class MobileEntity : public sge::StaticEntity{
        public:
            MobileEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups)
                : sge::StaticEntity(texture, textureRect, position, collisionGroups){
                    physicalObject = new PhysicalObject(sprite);
                    physicalObject->createContinuousComputation("update_velocity", sge::updateVelocityBasedOnAcceleration());
                    physicalObject->createContinuousComputation("update_position", sge::updatePositionBasedOnVelocity());
                }
    };
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

    class Scene : public sge::StatefulComponent{
        public:
            // rename to 'add' (parts are added)
            void addEntity(sf::View* view, sge::Entity* entity);
            void addEntities(sf::View* view, std::vector<sge::Entity*> entities);
            void addDebugEntity(sf::View* view, sge::DebugEntity* debugEntity);
            void addDebugEntities(sf::View* view, std::vector<sge::DebugEntity*> debugEntities);
        
            void activateSceneParts();
            void pauseSceneParts();
            void hideSceneParts();

        
            std::vector<sge::Entity*> getViewEntities(sf::View* view);
            std::unordered_map<sf::View*, std::vector<sge::Entity*>> getEntitiesMap();

            std::vector<sge::DebugEntity*> getViewDebugEntities(sf::View* view);
            std::unordered_map<sf::View*, std::vector<sge::DebugEntity*>> getDebugEntitiesMap();
            
        private:
            // Hidden because extended using 'activateScene', 'pauseScene' and 'hideScene'
            using sge::StatefulComponent::activate;
            using sge::StatefulComponent::pause;
            using sge::StatefulComponent::hide;
            // 

            std::unordered_map<sf::View*, std::vector<sge::Entity*>> m_entities;
            std::unordered_map<sf::View*, std::vector<sge::DebugEntity*>> m_debugEntities;
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
            SceneManager(sge::EntityManager* entityManager): m_entityManagerPtr(entityManager){};
            void setupDebug(sge::DebugManager* debugManager);
        
        protected:
            void m_registerSceneMembers(std::string label);
            void m_deregisterSceneMembers(std::string label);

            sge::EntityManager* m_entityManagerPtr = nullptr;
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

#ifndef DRUM_SCENE_MANAGER_H
#define DRUM_SCENE_MANAGER_H

namespace sge{
    class Scene;

    class DrumSceneManager : public sge::SceneManager{
        public:
            DrumSceneManager(sge::EntityManager* entityManager)
                : sge::SceneManager(entityManager){};

            void setCurrentScene(std::string name);
            void alignScene();

        private:
            std::string m_currentScene = "";
            std::string m_loadedScene = "";
    };
}

#endif
#ifndef LAYER_SCENE_MANAGER_H
#define LAYER_SCENE_MANAGER_H

#include <string>

namespace sge{
    class Scene;

    class LayerSceneManager : public sge::SceneManager{
        public:
            LayerSceneManager(sge::EntityManager* entityManager)
                : sge::SceneManager(entityManager){};

            void registerComponent(std::string label, sge::Scene* scene);
            void deregisterComponent(std::string label);
        
        private:
            // Hidden because extended
            using sge::SceneManager::registerComponent;
            using sge::SceneManager::deregisterComponent;
            //
    };
}

#endif

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
    sge::CollisionManager* CM = new sge::CollisionManager(CSM);
    sge::EntityManager* EM = new sge::EntityManager(SpM, PM, CSM, ClSM, STM, AnM, StM);
    sge::DrumSceneManager* DrSM = new sge::DrumSceneManager(EM);
    sge::LayerSceneManager* LaSM = new sge::LayerSceneManager(EM);

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
    drumSceneManager = DrSM;
    layerSceneManager = LaSM;
}

void sge::Universe::setupDebug(){
    sge::DebugManager* debugManagerPtr = new sge::DebugManager();
    debugManager = debugManagerPtr;

   drumSceneManager->setupDebug(debugManagerPtr);
   layerSceneManager->setupDebug(debugManagerPtr);
}

void sge::Universe::loop(){
    m_deltaClock.restart();

    while(m_windowPtr->isOpen()){
        // dt
        sf::Time deltaTime = m_deltaClock.restart();
        float dt = deltaTime.asSeconds();
        if(dt > dtCap) dt = dtCap;
        //

        // Event
        sf::Event event;
        while(m_windowPtr->pollEvent(event)){
            if(event.type == sf::Event::Closed) m_windowPtr->close();

            controllerManager->processEvent(event);
            m_clickableShapeManager->processEvent(event);
        }
        //

        // Update
        m_physicsManager->update(dt);
        m_collisionShapeManager->update(dt);
        m_clickableShapeManager->update(dt);
        m_spriteTextManager->update(dt);
        m_stateManager->update(dt);
        collisionManager->updateCollisions();

        m_animationManager->update(dt);
        scriptedViewManager->update(dt);

        drumSceneManager->alignScene(); // Scene can be reset only after all managers finished their updates to prevent segfaults in loops
        //

        
        // Draw
        m_windowPtr->clear();
        
        m_spriteManager->draw(m_windowPtr);
        m_spriteTextManager->draw(m_windowPtr);
        if(debugManager) debugManager->draw(m_windowPtr);

        m_windowPtr->display();
        //
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
sf::IntRect sge::TextureSheet::getTextureRect(int textureN, bool isFlippedHorizontally = false, bool isFlippedVertically = false){
    sf::IntRect rect = m_textureRects[textureN];

    if(isFlippedHorizontally){
        rect.left += rect.width;
        rect.width *= -1;
    }
    if(isFlippedVertically) rect.height *= -1;

    return rect;
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


void sge::DebugManager::draw(sf::RenderWindow* window){
    for(auto& [view, debugEntities]: m_components){
        window->setView(*view);
        
        for(sge::DebugEntity* debugEntity : debugEntities){
            if(debugEntity->isActive || debugEntity->isPaused){
                // Run extraDebugFunctions
                // !
                // ! rewrite into update or just remove
                // !
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
}


sge::CollisionShapeBorder::CollisionShapeBorder(sge::CollisionShape* owner, sge::CollisionShapeBorderSettings settings){
    this->setFillColor(sf::Color(0,0,0,0));

    this->setOutlineColor(settings.color);
    this->setOutlineThickness(settings.thickness);

    this->setPosition(sf::Vector2f(owner->getPosition().x + settings.thickness, owner->getPosition().y + settings.thickness));
    this->setSize(sf::Vector2f(owner->getSize().x - settings.thickness*2, owner->getSize().y - settings.thickness*2));
}


void sge::ControllerManager::processEvent(sf::Event event){
    for(sge::Controller* controller : m_components){
        controller->script(event);
    }
}


void sge::ScriptedViewManager::update(float dt){
    for(sge::ScriptedView* scriptedView : m_components){
        scriptedView->script();
    }
}


void sge::SpriteManager::draw(sf::RenderWindow* window){
    for(auto [view, sprites] : m_components){
        window->setView(*view);

        for(sge::Sprite* sprite : sprites){
            if(sprite->isActive || sprite->isPaused) window->draw(*sprite);
        }
    }
}


void sge::PhysicsManager::update(float dt){
    for(sge::PhysicalObject* physicalObject : m_components){
        if(physicalObject->isActive) physicalObject->update(dt);
    }
}


sge::PhysicalObject::PhysicalObject(sf::Sprite* ownerSprite){ m_ownerSpritePtr = ownerSprite; }

sf::Sprite* sge::PhysicalObject::getOwnerSprite(){ return m_ownerSpritePtr; }

void sge::PhysicalObject::createContinuousComputation(std::string name, std::function<void(sge::PhysicalObject*, float)> computation){
    m_continuousComputations[name] = computation;
    m_continuousComputationOrder.push_back(name);
}

void sge::PhysicalObject::update(float dt){
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

void sge::CollisionManager::updateCollisions(){
    std::vector<sge::Collision> presentCollisions;

    for(CollisionInteraction* collisionInteraction : m_components){
        for(std::string initiatorGroup : collisionInteraction->initiatorGroups){
            for(sge::CollisionShape* initiator : m_collisionShapeManagerPtr->getComponentsByCollisionGroup(initiatorGroup)){
                if(!initiator->isActive) continue;

                // Collect all present collisions
                for(std::string recipientGroup : collisionInteraction->recipientGroups){
                    for(sge::CollisionShape* recipient : m_collisionShapeManagerPtr->getComponentsByCollisionGroup(recipientGroup)){
                        if(!recipient->isActive) continue;

                        if(collisionInteraction->collisionDetectionAlgorithm(initiator, recipient)){
                            CollisionSide initiatorImpactSide = determineInitiatorImpactSide(initiator, recipient);

                            presentCollisions.push_back(sge::Collision{
                                initiator,
                                recipient,
                                initiatorImpactSide,
                                flipInitiatorImpactSide(initiatorImpactSide)
                            });
                        }
                    }
                }
                //

                std::vector<sge::Collision> pastCollisions = collisionInteraction->pastCollisions[initiator];

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
                    collisionInteraction->startPhaseCollisionResponse(startPhaseCollisions);

                if(continuousPhaseCollisions.size())
                    collisionInteraction->continuousPhaseCollisionResponse(continuousPhaseCollisions);
                
                if(endPhaseCollisions.size())
                    collisionInteraction->endPhaseCollisionResponse(endPhaseCollisions);
                //

                // Reset
                collisionInteraction->pastCollisions[initiator] = presentCollisions;
                presentCollisions.clear();
                //
            }
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

std::vector<sge::CollisionShape*> sge::CollisionShapeManager::getComponentsByCollisionGroup(std::string groupName){
    std::vector<sge::CollisionShape*> collisionGroupMembers;
    for(sge::CollisionShape* collisionShape : m_components){
        // if CollisionShape is a member of 'groupName' collision group
        if(std::find(collisionShape->collisionGroups.begin(), collisionShape->collisionGroups.end(), groupName) != collisionShape->collisionGroups.end()){
            collisionGroupMembers.push_back(collisionShape);
        }
    }

    return collisionGroupMembers;
}

void sge::CollisionShapeManager::update(float dt){
    for(sge::CollisionShape* collisionShape : m_components){
        if(collisionShape->isActive) collisionShape->align();
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
            if(clickableShape->isActive) clickableShape->align();
        }
    }
}

void sge::ClickableShapeManager::processEvent(sf::Event event){
    for(auto& [_, clickableShapes] : m_components){
        for(ClickableShape* clickableShape : clickableShapes){
            if(clickableShape->isActive) clickableShape->action(clickableShape, event);
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
            if(spriteText->isActive) spriteText->align();
        }
    }
}
void sge::SpriteTextManager::draw(sf::RenderWindow* window){
    for(auto& [view, spriteTextObjects] : m_components){
        window->setView(*view);

        for(SpriteText* spriteText : spriteTextObjects){
            if(spriteText->isActive || spriteText->isPaused) window->draw(*spriteText);
        }
    }
}


void sge::AnimationManager::update(float dt){
    for(sge::AnimationCluster* animation : m_components){
        if(animation->isActive) animation->run();
    }
}


void sge::AnimationCluster::addTextureSequence(std::string name, TextureSequence* textureSequence){ m_textureSequences[name] = textureSequence; }
void sge::AnimationCluster::setCurrentTextureSequence(std::string name){
    m_clock.restart();
    m_currentTextureSequence = name;
    m_currentTextureN = 0;

    m_updateTexture();
}

void sge::AnimationCluster::run(){
    if(!m_textureSequences.size()){
        printf("No texture sequences initialized.\n");
        exit(1);
    }
    if(!m_currentTextureSequence.length()){
        printf("Can not run AnimationCluster if no current texture sequence is set.\n"); // ? Default to first added ?
        exit(1);
    }

    if(m_clock.getElapsedTime().asMilliseconds() > animationDelayMilliseconds){
        m_updateTexture();

        if(m_currentTextureN+1 == m_textureSequences[m_currentTextureSequence]->sequenceRects.size()){
            m_currentTextureN = 0;
        }
        else m_currentTextureN++;

        m_clock.restart();
    }
}

void sge::AnimationCluster::m_updateTexture(){
    m_ownerSpritePtr->setTexture(*m_textureSequences[m_currentTextureSequence]->textureSheet->getTexture());
    m_ownerSpritePtr->setTextureRect(m_textureSequences[m_currentTextureSequence]->sequenceRects[m_currentTextureN]);
}


sge::TextureSequence::TextureSequence(std::vector<int> textureSequence, sge::TextureSheet* textureSheetPtr, bool isFlippedHorizontally = false, bool isFlippedVertically = false){
    textureSheet = textureSheetPtr;

    for(int n : textureSequence){
        sf::IntRect rect = textureSheet->getTextureRect(n, isFlippedHorizontally, isFlippedVertically);
        sequenceRects.push_back(rect);
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
        if(stateCluster->isActive) stateCluster->getCurrentState()->updateScript(dt, stateCluster);
    }
}


void sge::Entity::activateEntityParts(){
    sprite->activate();
    if(physicalObject) physicalObject->activate();
    if(!collisionShapes.empty()){
        for(auto& [_, collisionShape] : collisionShapes) collisionShape->activate();
    }
    if(clickableShape) clickableShape->activate();
    if(spriteText) spriteText->activate();
    if(animationCluster) animationCluster->activate();
    if(stateCluster) stateCluster->activate();

    sge::StatefulComponent::activate();
}

void sge::Entity::pauseEntityParts(){
    sprite->pause();
    if(physicalObject) physicalObject->pause();
    if(!collisionShapes.empty()){
        for(auto& [_, collisionShape] : collisionShapes) collisionShape->pause();
    }
    if(clickableShape) clickableShape->pause();
    if(spriteText) spriteText->pause();
    if(animationCluster) animationCluster->pause();
    if(stateCluster) stateCluster->pause();

    sge::StatefulComponent::pause();
}

void sge::Entity::hideEntityParts(){
    sprite->hide();
    if(physicalObject) physicalObject->hide();
    if(!collisionShapes.empty()){
        for(auto& [_, collisionShape] : collisionShapes) collisionShape->hide();
    }
    if(clickableShape) clickableShape->hide();
    if(spriteText) spriteText->hide();
    if(animationCluster) animationCluster->hide();
    if(stateCluster) stateCluster->hide();

    sge::StatefulComponent::hide();
}


sge::EntityManager::EntityManager(
        sge::SpriteManager* spriteManager,
        sge::PhysicsManager* physicsManager,
        sge::CollisionShapeManager* collisionShapeManager,
        sge::ClickableShapeManager* clickableShapeManager,
        sge::SpriteTextManager* spriteTextManager,
        sge::AnimationManager* animationManager,
        sge::StateManager* stateManager
    ){

    m_spriteManagerPtr = spriteManager;
    m_physicsManagerPtr = physicsManager;
    m_collisionShapeManagerPtr = collisionShapeManager;
    m_clickableShapeManagerPtr = clickableShapeManager;
    m_spriteTextManagerPtr = spriteTextManager;
    m_animationManagerPtr = animationManager;
    m_stateManagerPtr = stateManager;
}

void sge::EntityManager::registerComponent(sf::View* view, sge::Entity* entity){
    m_registerEntityMembers(view, entity);
    sge::ViewManager<sge::Entity*>::registerComponent(view, entity);
}
void sge::EntityManager::deregisterComponent(sf::View* view, sge::Entity* entity){
    m_deregisterEntityMembers(view, entity);
    sge::ViewManager<sge::Entity*>::deregisterComponent(view, entity);
}

void sge::EntityManager::m_registerEntityMembers(sf::View* view, sge::Entity* entity){
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
    
    if(entity->animationCluster){
        m_animationManagerPtr->registerComponent(entity->animationCluster);
    }

    if(entity->stateCluster){
        m_stateManagerPtr->registerComponent(entity->stateCluster);
    }
}

void sge::EntityManager::m_deregisterEntityMembers(sf::View* view, sge::Entity* entity){
    m_spriteManagerPtr->deregisterComponent(view, entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->deregisterComponent(entity->physicalObject);
    }

    if(entity->collisionShapes.size()){
        for(auto[_, collisionShape] : entity->collisionShapes){
            m_collisionShapeManagerPtr->deregisterComponent(collisionShape);
        }
    }

    if(entity->clickableShape){
        m_clickableShapeManagerPtr->deregisterComponent(view, entity->clickableShape);
    }

    if(entity->spriteText){
        m_spriteTextManagerPtr->deregisterComponent(view, entity->spriteText);
    }

    if(entity->animationCluster){
        m_animationManagerPtr->deregisterComponent(entity->animationCluster);
    }

    if(entity->stateCluster){
        m_stateManagerPtr->deregisterComponent(entity->stateCluster);
    }
}


void sge::Scene::addEntity(sf::View* view, sge::Entity* entity){ m_entities[view].push_back(entity); }
void sge::Scene::addEntities(sf::View* view, std::vector<sge::Entity*> entities){
    for(Entity* entity : entities){
        addEntity(view, entity);
    }
}
void sge::Scene::addDebugEntity(sf::View* view, sge::DebugEntity* debugEntity){ m_debugEntities[view].push_back(debugEntity); }
void sge::Scene::addDebugEntities(sf::View* view,std::vector<DebugEntity*> debugEntities){
    for(DebugEntity* debugEntity : debugEntities){
        addDebugEntity(view, debugEntity);
    }
}

void sge::Scene::activateSceneParts(){
    for(auto& [_, entities] : m_entities){
        for(sge::Entity* entity : entities){
            entity->activateEntityParts();
        }
    }
    for(auto& [_, debugEntities] : m_debugEntities){
        for(sge::DebugEntity* debugEntity : debugEntities){
            debugEntity->activate();
        }
    }

    sge::StatefulComponent::activate();
}
void sge::Scene::pauseSceneParts(){
    for(auto& [_, entities] : m_entities){
        for(sge::Entity* entity : entities){
            entity->pauseEntityParts();
        }
    }
    for(auto& [_, debugEntities] : m_debugEntities){
        for(sge::DebugEntity* debugEntity : debugEntities){
            debugEntity->pause();
        }
    }

    sge::StatefulComponent::pause();
}
void sge::Scene::hideSceneParts(){
    for(auto& [_, entities] : m_entities){
        for(sge::Entity* entity : entities){
            entity->hideEntityParts();
        }
    }
    for(auto& [_, debugEntities] : m_debugEntities){
        for(sge::DebugEntity* debugEntity : debugEntities){
            debugEntity->hide();
        }
    }

    sge::StatefulComponent::hide();
}

std::vector<sge::Entity*> sge::Scene::getViewEntities(sf::View* view){ return m_entities[view]; }
std::unordered_map<sf::View*, std::vector<sge::Entity*>> sge::Scene::getEntitiesMap(){ return m_entities; };

std::vector<sge::DebugEntity*> sge::Scene::getViewDebugEntities(sf::View* view){ return m_debugEntities[view]; }
std::unordered_map<sf::View*, std::vector<sge::DebugEntity*>> sge::Scene::getDebugEntitiesMap(){ return m_debugEntities; }


void sge::SceneManager::setupDebug(sge::DebugManager* debugManager){ m_debugManagerPtr = debugManager; }

void sge::SceneManager::m_registerSceneMembers(std::string label){
    for(auto& [view, entities] : m_components[label]->getEntitiesMap()){
        for(sge::Entity* entity : entities){
            m_entityManagerPtr->registerComponent(view, entity);
        }
    }

    if(m_debugManagerPtr){
        for(auto& [view, debugEntities] : m_components[label]->getDebugEntitiesMap()){
            for(sge::DebugEntity* debugEntity : debugEntities){
                m_debugManagerPtr->registerComponent(view, debugEntity);
            }
        }
    }
}

void sge::SceneManager::m_deregisterSceneMembers(std::string label){
    if(m_debugManagerPtr){
        for(auto& [view, debugEntities] : m_components[label]->getDebugEntitiesMap()){
            for(sge::DebugEntity* debugEntity : debugEntities){
                m_debugManagerPtr->deregisterComponent(view, debugEntity);
            }
        }
    }

    for(auto& [view, entities] : m_components[label]->getEntitiesMap()){
        for(sge::Entity* entity : entities){
            m_entityManagerPtr->deregisterComponent(view, entity);
        }
    }
}


void sge::DrumSceneManager::setCurrentScene(std::string name){ m_currentScene = name; }

void sge::DrumSceneManager::alignScene(){
    if(m_currentScene.length()){
        if(m_loadedScene != m_currentScene){
            if(m_loadedScene.length()) m_deregisterSceneMembers(m_loadedScene);

            m_registerSceneMembers(m_currentScene);

            m_loadedScene = m_currentScene;
        }
    }
}


void sge::LayerSceneManager::registerComponent(std::string label, sge::Scene* scene){
    sge::SceneManager::registerComponent(label, scene);
    m_registerSceneMembers(label);
}
void sge::LayerSceneManager::deregisterComponent(std::string label){
    m_deregisterSceneMembers(label);
    sge::SceneManager::deregisterComponent(label);
}


#endif