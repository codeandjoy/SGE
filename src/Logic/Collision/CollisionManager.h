#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include "../../Structure/Manager/StorageManagers/VectorManager.h"


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