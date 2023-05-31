#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <vector>


namespace sge{
    class StateCluster;

    class StateManager{
        public:
            void registerStateCluster(sge::StateCluster* stateCluster);
            void deregisterStateCluster(sge::StateCluster* stateCluster);


            void runUpdateScripts(float dt);

        private:
            std::vector<StateCluster*> m_stateClusters;
    }; 
}


#endif