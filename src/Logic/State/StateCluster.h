#ifndef STATE_CLUSTER_H
#define STATE_CLUSTER_H

#include <unordered_map>
#include <functional>
#include <string>

#include "../../Component/StatefulComponent.h"


namespace sge{
    struct State;

    class StateCluster : public sge::StatefulComponent{
        public:
            sge::State* getCurrentState();
            std::string getCurrentStateName();
            void setCurrentState(std::string name);


            std::unordered_map<std::string, sge::State*> states;
            
        private:
            std::string m_currentState = "";
    };
}


#endif