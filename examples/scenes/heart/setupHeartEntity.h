#ifndef SETUP_HEART_ENTITY_H
#define SETUP_HEART_ENTITY_H

#include "../../../SGE.hpp"

sge::Entity* setupHeartEntity(sge::Universe* universe, auto heartLayer){
    sge::Entity* heartEntity = sge::buildStaticEntity(
        universe->assetsManager->getTextureSheet("picoTiles")->getTexture(),
        universe->assetsManager->getTextureSheet("picoTiles")->getTextureRect(66),
        sf::Vector2f(heartLayer[0].getPosition().x, heartLayer[0].getPosition().y-10),
        {"heart"}
    );

    sge::Animation* heartAnimation = new sge::Animation(universe->assetsManager->getTextureSheet("picoTiles"), heartEntity->sprite, 66);
    heartAnimation->addTextureSequence("spin", std::vector<int>{66, 67, 68, 69, 70, 71});
    heartAnimation->setCurrentTextureSequence("spin");

    heartEntity->animation = heartAnimation;

    return heartEntity;
}


#endif