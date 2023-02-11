#ifndef CONTINUOUS_ACTION_H
#define CONTINUOUS_ACTION_H


struct ContinuousAction{
    bool shouldRun;
    std::function<void(float dt)> runAction;
};


#endif