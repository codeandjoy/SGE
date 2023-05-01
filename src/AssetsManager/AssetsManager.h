#ifndef ASSETS_MANAGER_H
#define ASSETS_MANAGER_H

#include <unordered_map>
#include <string>

#include "../Texture/TextureSheetSizes.h"


namespace sge{
    class TextureSheet;

    class AssetsManager{
        public:
            void loadTextureSheet(std::string location, std::string name, sge::TextureSheetSizes textureSheetSizes);
            sge::TextureSheet* getTextureSheet(std::string name);

            // TODO fonts

        private:
            std::unordered_map<std::string, sge::TextureSheet*> m_textures;
    };
}


#endif