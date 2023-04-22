#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <unordered_map>
#include <vector>
#include "TextureSheetSizes.h"

class TextureSheet;
class Animation;


class TextureManager{
    public:
        void loadTexture(std::string location, std::string name, TextureSheetSizes textureSheetSizes);
        TextureSheet* getTexture(std::string name);


        void registerAnimation(Animation* animation);
        void deregisterAnimation(Animation* animation);


        void initAnimationClocks();
        void updateAnimations();

    private:
        std::unordered_map<std::string, TextureSheet*> m_loadedTextures;
        std::vector<Animation*> m_animations;
};


#endif