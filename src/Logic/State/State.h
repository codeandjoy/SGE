#ifndef STATE_H
#define STATE_H

#include <functional>


namespace sge{
    class StateCluster;

    struct State{
        std::function<void()> enterScript = {};
        std::function<void()> exitScript = {};
        std::function<void(float, sge::StateCluster*)> updateScript = {};
    };
}


#endif