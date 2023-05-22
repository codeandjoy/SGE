#ifndef UI_SCREEN_H
#define UI_SCREEN_H

#include <vector>
#include <string>


namespace sge{
    struct UIEntity;
    class UIEntityManager;

    class UIScreen{
        public:
            void addUIEntity(sge::UIEntity* uiEntity);
            void removeUIEntity(sge::UIEntity* uiEntity);
            std::vector<sge::UIEntity*> getUIEntities();

            bool isVisible = true;

        private:
            std::vector<sge::UIEntity*> m_uiEntities;
    };
}


#endif