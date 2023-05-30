#include <algorithm>
#include <SFML/Graphics.hpp>

#include "ClickableShapeManager.h"
#include "ClickableShape.h"


void sge::ClickableShapeManager::registerClickableShape(sf::View* view, sge::ClickableShape* clickableShape){ m_clickableShapes[view].push_back(clickableShape); }
void sge::ClickableShapeManager::deregsiterClickableShape(sf::View* view, sge::ClickableShape* clickableShape){
    m_clickableShapes[view].erase(std::remove(m_clickableShapes[view].begin(), m_clickableShapes[view].end(), clickableShape), m_clickableShapes[view].end());
}
std::vector<sge::ClickableShape*> sge::ClickableShapeManager::getClickableShapesByView(sf::View* view){ return m_clickableShapes[view]; }
std::unordered_map<sf::View*, std::vector<sge::ClickableShape*>> sge::ClickableShapeManager::getClickableShapesMap(){ return m_clickableShapes; };


void sge::ClickableShapeManager::alignClickableShapes(){
    for(auto& [_, clickableShapes] : m_clickableShapes){
        for(sge::ClickableShape* clickableShape : clickableShapes){
            clickableShape->align();
        }
    }
}

void sge::ClickableShapeManager::updateClickableShapes(sf::Event event){
    for(auto& [_, clickableShapes] : m_clickableShapes){
        for(ClickableShape* thisClickableShape : clickableShapes){
            thisClickableShape->action(thisClickableShape, event);
        }
    }
}