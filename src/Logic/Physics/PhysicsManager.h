#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include <vector>

#include "../../Manager/StorageManagers/VectorManager.h"
#include "../../Manager/LoopSectionManagers/UpdateManager.h"


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