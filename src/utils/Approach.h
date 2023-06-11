#ifndef APPROACH_H
#define APPROACH_H


namespace sge{
    float approach(float goal, float step, float current){
        float diff = goal - current;

        if(step > abs(goal - current)) return goal;
        if(diff > step) return current + step;
        if(diff < -step) return current - step;
        return goal;
    }
}


#endif