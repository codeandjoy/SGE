#ifndef CONTINUOUS_COMPUTATION_H
#define CONTINUOUS_COMPUTATION_H


struct ContinuousComputation{
    bool shouldRun;
    std::function<void(float dt)> compute;
};


#endif