#ifndef CLICKABLE_SHAPE_MANAGER_H
#define CLICKABLE_SHAPE_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>


namespace sge{
    struct ClickableShape;

    class ClickableShapeManager{
        public:
            void registerClickableShape(sf::View* view, sge::ClickableShape* clickableShape);
            void deregsiterClickableShape(sf::View* view, sge::ClickableShape* clickableShape);
            std::vector<sge::ClickableShape*> getClickableShapesByView(sf::View* view);
            std::unordered_map<sf::View*, std::vector<sge::ClickableShape*>> getClickableShapesMap();

            void alignClickableShapes();
            void updateClickableShapes(sf::Event event);

        private:
            std::unordered_map<sf::View*, std::vector<sge::ClickableShape*>> m_clickableShapes;
    };
}


#endif