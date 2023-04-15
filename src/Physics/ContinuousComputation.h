#ifndef CONTINUOUS_CALCULATION_H
#define CONTINUOUS_CALCULATION_H


struct ContinuousComputation{
    bool shouldRun;
    std::function<void(float dt)> compute;
};


#endif