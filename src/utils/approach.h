#ifndef APPROACH_H
#define APPROACH_H

float approach(float goal, float current, float dt){
    float diff = goal - current;

    if(diff > dt) return current + dt;
    if(diff < -dt) return current - dt;
    return goal;
}

#endif