#include "Animation.h"

Animation::Animation(TextureSheet *spritesheet, sf::Sprite *owner, int initialTextureN){
    this->textureSheet = spritesheet;
    this->owner = owner;
    
    owner->setTexture(*spritesheet->getTextureSheet());
    owner->setTextureRect(spritesheet->getTextureRect(initialTextureN));
}

void Animation::run(){
    if(!currentAnimationSequence.length()){
        printf("Can not run animation if no currentAnimationSequence is set.\n"); // ? Default to first added ?
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

    // TODO dynamic animation delay (for each animation ?)
    if(clock.getElapsedTime().asMilliseconds() > 100){
        owner->setTextureRect(textureSheet->getTextureRect(animationSequences[currentAnimationSequence].at(currentTextureN)));
        
        if(currentTextureN+1 == animationSequences[currentAnimationSequence].size()){
            currentTextureN = 0;
        }
        else currentTextureN++;

        
        clock.restart();
    }
}

void Animation::restartClock(){
    clock.restart();
}

void Animation::setCurrentAnimationSequence(std::string sequenceName){
    if(currentAnimationSequence != sequenceName){
        currentAnimationSequence = sequenceName;
        currentTextureN = 0;
        clock.restart();
    }
}

void Animation::addAnimationSequence(std::string sequenceName, std::vector<int> textureSequence){
    // Ensure uniqueness
    if(animationSequences.count(sequenceName)){
        printf("Animation '%s' already exists.\n", sequenceName.c_str());
        return;
    }
    
    animationSequences[sequenceName] = textureSequence;
}