#ifndef TEXTURE_SHEET_SIZES_H
#define TEXTURE_SHEET_SIZES_H


struct TextureSheetSizes{
    int textureSizeX;
    int textureSizeY;
    int numTexturesX;
    int numTexturesY;

    TextureSheetSizes(int textureSizeX_, int textureSizeY_, int numTexturesX_, int numTexturesY_){
        textureSizeX = textureSizeX_;
        textureSizeY = textureSizeY_;
        numTexturesX = numTexturesX_;
        numTexturesY = numTexturesY_;
    }

};


#endif