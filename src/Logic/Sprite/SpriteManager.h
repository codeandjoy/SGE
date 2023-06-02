#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../../Manager/StorageManagers/ViewManager.h"
#include "../../Manager/LoopSectionManagers/DrawManager.h"


namespace sge{
    class SpriteManager :
        public sge::ViewManager<sf::Sprite*>,
        public sge::DrawManager{
            
        public:
            void draw(sf::RenderWindow* window) override;
    };
}


#endif