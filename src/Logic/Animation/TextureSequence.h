#ifndef TEXTURE_SEQUENCE_H
#define TEXTURE_SEQUENCE_H

#include <SFML/Graphics.hpp>
#include <vector>


namespace sge{
    class TextureSheet;    

    class TextureSequence{
        public:
            TextureSequence(std::vector<int> textureSequence, sge::TextureSheet* textureSheetPtr, bool isFlippedHorizontally, bool isFlippedVertically);

            std::vector<sf::IntRect> sequenceRects;
            TextureSheet* textureSheet;
            // TODO create runForward / cycle flags and use them in 'Animation'
    };
}


#endif