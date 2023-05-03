#ifndef UI_ENTITY_MANAGER_H
#define UI_ENTITY_MANAGER_H

#include <vector>


namespace sge{
    class UISpriteManager;
    class ClickableShapeManager;
    class SpriteTextManager;
    class UIAnimationManager;
    struct UIEntity;

    class UIEntityManager{
        public:
            UIEntityManager(sge::UISpriteManager* uiSpriteManager, sge::ClickableShapeManager* clickableShapeManager, sge::SpriteTextManager* spriteTextManager, sge::UIAnimationManager* uiAnimationManager);


            void registerUIEntity(sge::UIEntity* uiEntity);
            void deregisterUIEntity(sge::UIEntity* uiEntity);
            void deregisterAllUIEntities();


            void showUIEntity(sge::UIEntity* uiEntity);
            void hideUIEntity(sge::UIEntity* uiEntity);

        private:
            std::vector<sge::UIEntity*> m_uiEntities;

            sge::UISpriteManager* m_uiSpriteManager;
            sge::ClickableShapeManager* m_clickableShapeManager;
            sge::SpriteTextManager* m_spriteTextManager;
            sge::UIAnimationManager* m_uiAnimationManager;
    };
}


#endif