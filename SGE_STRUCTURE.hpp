#ifndef SGE_HPP
#define SGE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "./src/Universe/Universe.h"

// AssetsManager
#include "./src/Assets/AssetsManager/AssetsManager.h"
#include "./src/Assets/Texture/TextureSheetSizes.h"
#include "./src/Assets/Texture/TextureSheet.h"
//


// Common
#include "./src/Common/Animation/Animation.h"

#include "./src/Common/ClickableShape/ClickableShape.h"
#include "./src/Common/ClickableShape/ClickableShapeManager.h"
#include "./src/Common/ClickableShape/helpers.h"
//


// Debug
#include "./src/Debug/DebugEntity/DebugEntity.h"
#include "./src/Debug/DebugManager/DebugManager.h"
#include "./src/Debug/CollisionShapeBorder/CollisionShapeBorder.h"
#include "./src/Debug/CollisionShapeBorder/CollisionShapeBorderSettings.h"
//


// Logic
#include "./src/Logic/Controller/ControllerManager.h"

#include "./src/Logic/ScriptedView/ScriptedView.h"
#include "./src/Logic/ScriptedView/ScriptedViewManager.h"
#include "./src/Logic/SpriteManager/SpriteManager.h"

#include "./src/Logic/Physics/PhysicsManager.h"
#include "./src/Logic/Physics/PhysicalObject.h"
#include "./src/Logic/Physics/Computations.h"

#include "./src/Logic/Collision/CollisionManager.h"
#include "./src/Logic/Collision/CollisionPair.h"
#include "./src/Logic/Collision/CollisionSide.h"
#include "./src/Logic/Collision/Collision.h"
#include "./src/Logic/Collision/CollisionUtils.h"
#include "./src/Logic/CollisionShape/CollisionShape.h"
#include "./src/Logic/CollisionShape/CollisionShapeManager.h"
#include "./src/Logic/Collision/CollisionResponses.h"
#include "./src/Logic/Collision/CollisionDetectionAlgorithms.h"

#include "./src/Logic/AnimationManager/AnimationManager.h"

#include "./src/Logic/Entity/Entity.h"
#include "./src/Logic/Entity/EntityManager.h"
#include "./src/Logic/Entity/EntityBuilders.h"

#include "./src/Logic/Scene/Scene.h"
#include "./src/Logic/Scene/SceneManager.h"
//

// UI
#include "./src/UI/UIScreen/UIScreen.h"
#include "./src/UI/UIScreen/UIScreenManager.h"

#include "./src/UI/UISpriteManager/UISpriteManager.h"

#include "./src/UI/SpriteText/SpriteText.h"
#include "./src/UI/SpriteText/SpriteTextManager.h"

#include "./src/UI/UIEntity/UIEntity.h"
#include "./src/UI/UIEntity/UIEntityManager.h"

#include "./src/UI/UIAnimationManager/UIAnimationManager.h"
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