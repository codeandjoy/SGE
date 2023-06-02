#include <vector>

#include "../../Manager/StorageManagers/VectorManager.h"
#include "../../Manager/LoopSectionManagers/UpdateManager.h"


namespace sge{
    class Animation;

    class AnimationManager :
        public sge::VectorManager<sge::Animation*>,
        public sge::UpdateManager{
        
        public:
            void update(float dt) override;
    };
}