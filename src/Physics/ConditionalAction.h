#ifndef CONDITIONAL_ACTION_H
#define CONDITIONAL_ACTION_H


struct ConditionalAction{
    std::function<bool()> condition;
    std::function<void()> runAction; // ? Make function variadic ?
};


#endif