#include <vector>


namespace sge{
    class Animation;    

    class AnimationManager{
        public:
            void registerAnimation(sge::Animation* animation);
            void deregisterAnimation(sge::Animation* animation);
            void deregisterAllAnimations();

            void initAnimationClocks();
            void updateAnimations();

        private:
            std::vector<sge::Animation*> m_animations;
    };
}