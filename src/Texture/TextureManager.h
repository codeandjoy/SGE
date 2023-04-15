#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "TextureSheetSizes.h"
#include "TextureSheet.h"
#include "Animation.h"


class TextureManager{
    public:
        void loadTexture(std::string location, std::string name, TextureSheetSizes textureSheetSizes);
        TextureSheet* getTexture(std::string name);


        void registerAnimation(Animation* animation);
        void deregisterAnimation(Animation* animation);


        void initAnimationClocks();
        void updateAnimations();

    private:
        std::map<std::string, TextureSheet*> m_loadedTextures;
        std::vector<Animation*> m_animations;
};


#endif