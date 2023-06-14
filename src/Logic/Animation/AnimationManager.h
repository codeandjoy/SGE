#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <vector>

#include "../../Structure/Manager/StorageManagers/VectorManager.h"
#include "../../Structure/Manager/LoopSectionManagers/UpdateManager.h"


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