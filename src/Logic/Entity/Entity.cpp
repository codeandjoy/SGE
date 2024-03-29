#include "Entity.h"
#include "../Sprite/Sprite.h"
#include "../Physics/MotionUnit.h"
#include "../CollisionShape/CollisionShape.h"
#include "../ClickableShape/ClickableShape.h"
#include "../SpriteText/SpriteText.h"
#include "../Animation/AnimationCluster.h"
#include "../State/StateCluster.h"

void sge::Entity::activateEntityParts(){
    sprite->activate();
    if(motionUnit) motionUnit->activate();
    if(!collisionShapes.empty()){
        for(auto& [_, collisionShape] : collisionShapes) collisionShape->activate();
    }
    if(clickableShape) clickableShape->activate();
    if(spriteText) spriteText->activate();
    if(animationCluster) animationCluster->activate();
    if(stateCluster) stateCluster->activate();

    sge::StatefulComponent::activate();
}

void sge::Entity::pauseEntityParts(){
    sprite->pause();
    if(motionUnit) motionUnit->pause();
    if(!collisionShapes.empty()){
        for(auto& [_, collisionShape] : collisionShapes) collisionShape->pause();
    }
    if(clickableShape) clickableShape->pause();
    if(spriteText) spriteText->pause();
    if(animationCluster) animationCluster->pause();
    if(stateCluster) stateCluster->pause();

    sge::StatefulComponent::pause();
}

void sge::Entity::hideEntityParts(){
    sprite->hide();
    if(motionUnit) motionUnit->hide();
    if(!collisionShapes.empty()){
        for(auto& [_, collisionShape] : collisionShapes) collisionShape->hide();
    }
    if(clickableShape) clickableShape->hide();
    if(spriteText) spriteText->hide();
    if(animationCluster) animationCluster->hide();
    if(stateCluster) stateCluster->hide();

    sge::StatefulComponent::hide();
}