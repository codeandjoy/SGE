#ifndef SCRIPTED_VIEW_MANAGER_H
#define SCRIPTED_VIEW_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "../Structure/Manager/StorageManagers/VectorManager.h"
#include "../Structure/Manager/LoopSectionManagers/UpdateManager.h"


namespace sge{
    struct ScriptedView;

    class ScriptedViewManager :
        public sge::VectorManager<sge::ScriptedView*>,
        public sge::UpdateManager{

        public:
            void update(float dt) override;
    };
}


#endif