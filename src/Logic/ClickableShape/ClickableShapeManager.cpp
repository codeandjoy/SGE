#include <algorithm>
#include <SFML/Graphics.hpp>

#include "ClickableShapeManager.h"
#include "ClickableShape.h"


void sge::ClickableShapeManager::update(float dt){
    for(auto& [_, clickableShapes] : m_components){
        for(sge::ClickableShape* clickableShape : clickableShapes){
            clickableShape->align();
        }
    }
}

void sge::ClickableShapeManager::processEvent(sf::Event event){
    for(auto& [_, clickableShapes] : m_components){
        for(ClickableShape* thisClickableShape : clickableShapes){
            thisClickableShape->action(thisClickableShape, event);
        }
    }
}