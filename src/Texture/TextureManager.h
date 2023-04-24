#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "TextureSheetSizes.h"


namespace sge{
    class TextureSheet;
    class Animation;

    class TextureManager{
        public:
            void loadTexture(std::string location, std::string name, sge::TextureSheetSizes textureSheetSizes);
            sge::TextureSheet* getTexture(std::string name);


            void registerAnimation(sge::Animation* animation);
            void deregisterAnimation(sge::Animation* animation);


            void initAnimationClocks();
            void updateAnimations();

        private:
            std::unordered_map<std::string, sge::TextureSheet*> m_loadedTextures;
            std::vector<sge::Animation*> m_animations;
    };
}


#endif