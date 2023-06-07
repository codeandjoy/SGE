#include "TextureSequence.h"
#include "../../Assets/Texture/TextureSheet.h"


sge::TextureSequence::TextureSequence(std::vector<int> textureSequence, sge::TextureSheet* textureSheetPtr, bool isFlippedHorizontally = false, bool isFlippedVertically = false){
    textureSheet = textureSheetPtr;

    for(int n : textureSequence){
        sf::IntRect rect = textureSheet->getTextureRect(n, isFlippedHorizontally, isFlippedVertically);
        sequenceRects.push_back(rect);
    }
}