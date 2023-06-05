#ifndef SETUP_PLAYER_ENTITY_H
#define SETUP_PLAYER_ENTITY_H

#include "../../../SGE.hpp"


sge::Entity* setupPlayerEntity(sge::Universe* universe){
    sge::Entity* playerEntity = sge::buildMobileEntity(
        universe->assetsManager->getTextureSheet("knight")->getTexture(),
        universe->assetsManager->getTextureSheet("knight")->getTextureRect(9),
        sf::Vector2f(100,50),
        {"player"}
    );

    playerEntity->physicalObject->acceleration.y = .2;

    sge::Animation* playerAnimation = new sge::Animation(universe->assetsManager->getTextureSheet("knight"), playerEntity->sprite, 9);
    playerAnimation->addTextureSequence("idle", std::vector<int>{9});
    playerAnimation->addTextureSequence("runRight", std::vector<int>{33, 34, 35});
    playerAnimation->addTextureSequence("runLeft", std::vector<int>{45, 46, 47});
    playerAnimation->setCurrentTextureSequence("idle");

    playerEntity->animation = playerAnimation;

    return playerEntity;
}


#endif