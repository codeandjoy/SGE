#ifndef SPRITE_TEXT_MANAGER_H
#define SPRITE_TEXT_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../../Structure/Manager/StorageManagers/ViewManager.h"
#include "../../Structure/Manager/LoopSectionManagers/UpdateManager.h"
#include "../../Structure/Manager/LoopSectionManagers/DrawManager.h"


namespace sge{
    class SpriteText;

    class SpriteTextManager :
        public sge::ViewManager<sge::SpriteText*>,
        public sge::UpdateManager,
        public sge::DrawManager{
            
        public:
            void update(float dt) override;
            void draw(sf::RenderWindow* window) override;
    };  
}


#endif