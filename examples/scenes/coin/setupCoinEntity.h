#ifndef SETUP_COIN_ENTITY_H
#define SETUP_COIN_ENTITY_H

#include "../../../SGE.hpp"


sge::Entity* setupCoinEntity(sge::Universe* universe, auto coinLayer){
    sge::Entity* coinEntity = sge::buildStaticEntity(
        universe->assetsManager->getTextureSheet("picoTiles")->getTexture(),
        universe->assetsManager->getTextureSheet("picoTiles")->getTextureRect(18),
        sf::Vector2f(coinLayer[0].getPosition().x, coinLayer[0].getPosition().y-10),
        {"coin"}
    );

    sge::Animation* coinAnimation = new sge::Animation(universe->assetsManager->getTextureSheet("picoTiles"), coinEntity->sprite, 18);
    coinAnimation->addTextureSequence("spin", std::vector<int>{18, 19, 20, 21, 22, 23});
    coinAnimation->setCurrentTextureSequence("spin");

    coinEntity->animation = coinAnimation;

    return coinEntity;
}


#endif