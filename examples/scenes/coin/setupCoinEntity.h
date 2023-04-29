#ifndef SETUP_COIN_ENTITY_H
#define SETUP_COIN_ENTITY_H

#include "../../../SGE.hpp"


sge::Entity* setupCoinEntity(sge::Universe* universe, auto coinLayer){
    sge::Entity* coinEntity = sge::buildStaticEntity(
        universe->textureManager->getTexture("picoTiles")->getTextureSheet(),
        universe->textureManager->getTexture("picoTiles")->getTextureRect(18),
        sf::Vector2f(coinLayer[0].getPosition().x, coinLayer[0].getPosition().y-10)
    );

    sge::Animation* coinAnimation = new sge::Animation(universe->textureManager->getTexture("picoTiles"), coinEntity->physicalObject, 18);
    coinAnimation->addTextureSequence("spin", std::vector<int>{18, 19, 20, 21, 22, 23});
    coinAnimation->setCurrentTextureSequence("spin");

    coinEntity->animation = coinAnimation;

    return coinEntity;
}


#endif