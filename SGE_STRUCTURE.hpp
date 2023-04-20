//namespace sge{

#ifndef SGE_HPP
#define SGE_HPP

#include <SFML/Graphics.hpp>

#include "./src/Universe/Universe.h"

#include "./src/Texture/TextureSheet.h"
#include "./src/Texture/TextureSheetSizes.h"
#include "./src/Texture/TextureManager.h"
#include "./src/Texture/Animation.h"

#include "./src/Physics/PhysicsManager.h"
#include "./src/Physics/PhysicalObject.h"
#include "./src/Physics/ContinuousComputation.h"
#include "./src/Physics/computations.h"

#include "./src/Collision/CollisionManager.h"
#include "./src/Collision/CollisionPair.h"
#include "./src/Collision/CollisionResponses.h"
#include "./src/Collision/CollisionDetectionAlgorithms.h"
#include "./src/Collision/CollisionSide.h"
#include "./src/Collision/Collision.h"
#include "./src/Collision/CollisionUtils.h"
#include "./src/Collision/CollisionShape.h"

#include "./src/Entity/Entity.h"
#include "./src/Entity/EntityManager.h"
#include "./src/Entity/EntityBuilders.h"

#include "./src/Debug/DebugEntity.h"
#include "./src/Debug/DebugManager.h"
#include "./src/Debug/CollisionShapeBorder.h"
#include "./src/Debug/CollisionShapeBorderSettings.h"

#include "./src/utils/approach.h"
#include "./src/utils/Measurements.h"

#endif

#ifndef SGE_MAIN

// -> stitch <-

#endif

//}