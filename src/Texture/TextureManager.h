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
        void addAnimation(std::string name, Animation* animation);
        Animation* getAnimation(std::string name);
        void deleteAnimation(std::string name);
        // *

        void initAnimationClocks();
        void updateAnimations();

    private:
        std::map<std::string, TextureSheet*> loadedTextures;
        std::map<std::string, Animation*> animations;
};


#endif