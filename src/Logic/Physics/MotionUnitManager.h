#ifndef MOTION_UNIT_MANAGER_H
#define MOTION_UNIT_MANAGER_H

#include <vector>

#include "../../Structure/Manager/StorageManagers/VectorManager.h"
#include "../../Structure/Manager/LoopSectionManagers/UpdateManager.h"


namespace sge{
    class MotionUnit;

    class MotionUnitManager :
        public sge::VectorManager<sge::MotionUnit*>,
        public sge::UpdateManager{

        public:
            void update(float dt) override;
    };
}


#endif