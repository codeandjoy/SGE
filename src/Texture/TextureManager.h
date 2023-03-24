#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "TextureSheetSizes.h"
#include "TextureSheet.h"


class TextureManager{
    public:
        void load(std::string textureLocation, TextureSheetSizes textureSheetSizes, std::string textureName);
        TextureSheet* get(std::string textureName); // TODO check nonexistent data (return nullptr?)
        // ? not needed
        TextureSheet* getByLocation(std::string textureLocation); // can be used to check whether texture at location has been loaded

    private:
        std::map<std::string, TextureSheet*> loadedTextures;
};


#endif