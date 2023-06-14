#ifndef COLLISION_SHAPE_MANAGER_H
#define COLLISION_SHAPE_MANAGER_H

#include <vector>

#include "../../Structure/Manager/StorageManagers/VectorManager.h"
#include "../../Structure/Manager/LoopSectionManagers/UpdateManager.h"


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