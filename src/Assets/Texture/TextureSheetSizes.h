#ifndef TEXTURE_SHEET_SIZES_H
#define TEXTURE_SHEET_SIZES_H


namespace sge{
    struct TextureSheetSizes{
        int textureSizeX;
        int textureSizeY;
        int numTexturesX;
        int numTexturesY;
        int gapX = 0;
        int gapY = 0;
    };
}


#endif