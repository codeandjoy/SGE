#ifndef UI_ANIMATION_MANAGER_H
#define UI_ANIMATION_MANAGER_H

#include <vector>


namespace sge{
    class Animation;

    class UIAnimationManager{
        public:
            void registerAnimation(sge::Animation* animation);
            void deregisterAnimation(sge::Animation* animation);
            std::vector<sge::Animation*> getAllActiveAnimations();


            void activateAnimation(sge::Animation* animation);
            void deactivateAnimation(sge::Animation* animation);

            void initAnimationClocks();
            void updateActiveAnimations();

        private:
            std::vector<sge::Animation*> m_activeAnimations;
            std::vector<sge::Animation*> m_inactiveAnimations;
    };
}


#endif