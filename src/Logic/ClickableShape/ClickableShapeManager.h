#ifndef CLICKABLE_SHAPE_MANAGER_H
#define CLICKABLE_SHAPE_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../../Manager/StorageManagers/ViewManager.h"
#include "../../Manager/LoopSectionManagers/UpdateManager.h"
#include "../../Manager/LoopSectionManagers/EventManager.h"


namespace sge{
    struct ClickableShape;

    class ClickableShapeManager :
        public sge::ViewManager<ClickableShape*>,
        public sge::UpdateManager,
        public sge::EventManager{

        public:
            void update(float dt) override;
            void processEvent(sf::Event event) override;
    };
}


#endif