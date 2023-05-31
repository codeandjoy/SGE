#ifndef STATE_H
#define STATE_H

#include <functional>


namespace sge{
    struct State{
        std::function<void()> enterScript = {};
        std::function<void()> exitScript = {};
        std::function<void(float dt)> updateScript = {};
    };
}


#endif