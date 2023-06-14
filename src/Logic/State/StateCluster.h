#ifndef STATE_CLUSTER_H
#define STATE_CLUSTER_H

#include <unordered_map>
#include <functional>
#include <vector>
#include <string>

#include "../../Structure/Component/StatefulComponent.h"


namespace sge{
    struct State;

    class StateCluster : public sge::StatefulComponent{
        public:
            std::vector<sge::State*> getActiveStates();
            std::vector<std::string> getActiveStateNames();
            void activateState(std::string name);
            void deactivateState(std::string name);

            bool isStateActive(std::string name);

            std::unordered_map<std::string, sge::State*> states;
            
        private:
            std::vector<std::string> m_activeStates;
    };
}


#endif