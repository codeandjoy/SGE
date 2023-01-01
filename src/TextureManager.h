#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "TextureSheetSizes.h"
#include "TextureSheet.h"


class TextureManager{
    public:
        void load(std::string textureLocation, TextureSheetSizes textureSheetSizes, std::string textureName);
        bool isLoaded(std::string textureLocation);
        TextureSheet* get(std::string textureName);

    private:
        std::map<std::string, TextureSheet*> loadedTextures;
};


#endif