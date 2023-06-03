#include "Entity.h"
#include "../Sprite/Sprite.h"
#include "../Physics/PhysicalObject.h"
#include "../CollisionShape/CollisionShape.h"
#include "../ClickableShape/ClickableShape.h"
#include "../SpriteText/SpriteText.h"
#include "../Animation/Animation.h"
#include "../State/StateCluster.h"

void sge::Entity::activateEntity(){
    sprite->activate();
    if(physicalObject) physicalObject->activate();
    if(!collisionShapes.empty()){
        for(auto& [_, collisionShape] : collisionShapes) collisionShape->activate();
    }
    if(clickableShape) clickableShape->activate();
    if(spriteText) spriteText->activate();
    if(animation) animation->activate();
    if(stateCluster) stateCluster->activate();
}

void sge::Entity::pauseEntity(){
    sprite->pause();
    if(physicalObject) physicalObject->pause();
    if(!collisionShapes.empty()){
        for(auto& [_, collisionShape] : collisionShapes) collisionShape->pause();
    }
    if(clickableShape) clickableShape->pause();
    if(spriteText) spriteText->pause();
    if(animation) animation->pause();
    if(stateCluster) stateCluster->pause();
}

void sge::Entity::hideEntity(){
    sprite->hide();
    if(physicalObject) physicalObject->hide();
    if(!collisionShapes.empty()){
        for(auto& [_, collisionShape] : collisionShapes) collisionShape->hide();
    }
    if(clickableShape) clickableShape->hide();
    if(spriteText) spriteText->hide();
    if(animation) animation->hide();
    if(stateCluster) stateCluster->hide();
}