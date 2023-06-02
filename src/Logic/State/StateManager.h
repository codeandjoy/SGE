#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <vector>

#include "../../Manager/StorageManagers/VectorManager.h"
#include "../../Manager/LoopSectionManagers/UpdateManager.h"


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