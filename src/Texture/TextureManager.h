#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "TextureSheetSizes.h"
#include "TextureSheet.h"
#include "Animation.h"


class TextureManager{
    public:
        // * Textures
        void loadTexture(std::string location, std::string name, TextureSheetSizes textureSheetSizes);
        TextureSheet* getTexture(std::string name); // TODO check nonexistent data (return nullptr?)
        // *

        // * Animations
        void registerAnimation(Animation* animation);
        void deregisterAnimation(Animation* animation);
        // *

        void initAnimationClocks();
        void updateAnimations();

    private:
        std::map<std::string, TextureSheet*> loadedTextures;
        std::vector<Animation*> animations;
};


#endif