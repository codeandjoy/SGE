#include "Animation.h"

Animation::Animation(Spritesheet *spritesheet, sf::Sprite *owner, int initialTextureN){
    this->spritesheet = spritesheet;
    this->owner = owner;
    
    owner->setTexture(*spritesheet->getSpritesheet());
    owner->setTextureRect(spritesheet->getTextureRect(initialTextureN));
}

void Animation::run(){
    if(!currentAnimation.length()){
        printf("Can not run animation if no currentAnimation is set.\n"); // ? Default to first added ?
        if(animationSequences.size()){
            printf("Available animations:\n");
            for(auto const &pair: animationSequences){
                printf("%s\n", pair.first.c_str());
            }
        }
        else{
            printf("No animation sequences initialized.\n");
        }
        exit(1);
    }

    if(clock.getElapsedTime().asMilliseconds() > 100){
        owner->setTextureRect(spritesheet->getTextureRect(animationSequences[currentAnimation].at(currentTextureN)));
        
        if(currentTextureN+1 == animationSequences[currentAnimation].size()){
            currentTextureN = 0;
        }
        else currentTextureN++;

        
        clock.restart();
    }
}

void Animation::restartClock(){
    clock.restart();
}

void Animation::setCurrentAnimation(std::string animationName){
    if(currentAnimation != animationName){
        currentAnimation = animationName;
        currentTextureN = 0;
        clock.restart();
    }
}

void Animation::addAnimationSequence(std::string animationName, std::vector<int> textureSequence){
    // Ensure uniqueness
    if(animationSequences.count(animationName)){
        printf("Animation '%s' already exists.\n", animationName.c_str());
        return;
    }
    
    animationSequences[animationName] = textureSequence;
}