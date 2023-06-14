#ifndef SGE_HPP
#define SGE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "./src/Universe/Universe.h"

// Manager
#include "./src/Structure/Manager/StorageManagers/VectorManager.h"
#include "./src/Structure/Manager/StorageManagers/ViewManager.h"
#include "./src/Structure/Manager/StorageManagers/LabelManager.h"
//


// Component
#include "./src/Structure/Component/StatefulComponent.h"
//


// AssetsManager
#include "./src/Assets/AssetsManager/AssetsManager.h"
#include "./src/Assets/Texture/TextureSheetSizes.h"
#include "./src/Assets/Texture/TextureSheet.h"
//


// Debug
#include "./src/Debug/DebugEntity/DebugEntity.h"
#include "./src/Debug/DebugEntity/DebugEntityManager.h"
#include "./src/Debug/DebugEntity/CollisionShapeBorder/CollisionShapeBorder.h"
#include "./src/Debug/DebugEntity/CollisionShapeBorder/CollisionShapeBorderSettings.h"

#include "./src/Debug/DebugScreen/DebugScreenManager.h"
#include "./src/Debug/DebugScreen/DebugVariable.h"
//


// Controller
#include "./src/Controller/Controller.h"
#include "./src/Controller/ControllerManager.h"
//


// View
#include "./src/View/ScriptedView.h"
#include "./src/View/ScriptedViewManager.h"
//


// Logic
#include "./src/Logic/Sprite/Sprite.h"
#include "./src/Logic/Sprite/SpriteManager.h"

#include "./src/Logic/Physics/MotionUnitManager.h"
#include "./src/Logic/Physics/MotionUnit.h"
#include "./src/Logic/Physics/ComputationScripts.h"

#include "./src/Logic/Collision/CollisionManager.h"
#include "./src/Logic/Collision/CollisionInteraction.h"
#include "./src/Logic/Collision/CollisionSide.h"
#include "./src/Logic/Collision/Collision.h"
#include "./src/Logic/Collision/CollisionUtils.h"
#include "./src/Logic/CollisionShape/CollisionShape.h"
#include "./src/Logic/CollisionShape/CollisionShapeManager.h"
#include "./src/Logic/Collision/CollisionResponses.h"
#include "./src/Logic/Collision/CollisionDetectionAlgorithms.h"

#include "./src/Logic/ClickableShape/ClickableShape.h"
#include "./src/Logic/ClickableShape/ClickableShapeManager.h"
#include "./src/Logic/ClickableShape/helpers.h"

#include "./src/Logic/SpriteText/SpriteText.h"
#include "./src/Logic/SpriteText/SpriteTextManager.h"

#include "./src/Logic/Animation/AnimationManager.h"
#include "./src/Logic/Animation/AnimationCluster.h"
#include "./src/Logic/Animation/TextureSequence.h"

#include "./src/Logic/State/State.h"
#include "./src/Logic/State/StateCluster.h"
#include "./src/Logic/State/StateManager.h"

#include "./src/Logic/Entity/Entity.h"
#include "./src/Logic/Entity/EntityManager.h"
#include "./src/Logic/Entity/EntityBuilds/PlainEntity.h"
#include "./src/Logic/Entity/EntityBuilds/VoidEntity.h"
#include "./src/Logic/Entity/EntityBuilds/StaticEntity.h"
#include "./src/Logic/Entity/EntityBuilds/MobileEntity.h"
#include "./src/Logic/Entity/EntityBuilds/SimpleMobileEntity.h"
#include "./src/Logic/Entity/EntityBuilds/ComplexMobileEntity.h"

#include "./src/Logic/Scene/Scene.h"
#include "./src/Logic/Scene/SceneManager.h"
//


// utils
#include "./src/utils/Approach.h"
#include "./src/utils/Measurements.h"
//

#endif

#ifndef SGE_MAIN
#define SGE_MAIN

// -> stitch <-

#endif