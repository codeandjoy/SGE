#ifndef CLICKABLE_SHAPE_MANAGER_H
#define CLICKABLE_SHAPE_MANAGER_H

#include <vector>


namespace sge{
    struct ClickableShape;

    class ClickableShapeManager{
        public:
            void registerClickableShape(sge::ClickableShape* clickableShape);
            void deregsiterClickableShape(sge::ClickableShape* clickableShape);
            std::vector<sge::ClickableShape*> getAllActiveClickableShapes();


            void activateClickableShape(sge::ClickableShape* clickableShape);
            void deactivateClickableShape(sge::ClickableShape* clickableShape);


            void alignClickableShapes();
            void updateClickableShapes(sf::Event event);

        private:
            std::vector<sge::ClickableShape*> m_activeClickableShapes;
            std::vector<sge::ClickableShape*> m_inactiveClickableShapes;
    };
}


#endif