#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../../Structure/Manager/StorageManagers/ViewManager.h"
#include "../../Structure/Manager/LoopSectionManagers/DrawManager.h"


namespace sge{
    class Sprite;

    class SpriteManager :
        public sge::ViewManager<sge::Sprite*>,
        public sge::DrawManager{
            
        public:
            void draw(sf::RenderWindow* window) override;
    };
}


#endif