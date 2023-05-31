#ifndef STATE_H
#define STATE_H

#include <functional>


namespace sge{
    class StateCluster;
    struct Entity;

    class State{
        public:
            State(Entity* ownerEntity);

            virtual void enterScript(){}
            virtual void exitScript(){}
            virtual void updateScript(float dt, sge::StateCluster* containerStateCluster){}

        protected:
            Entity* m_ownerEntityPtr;
    };
}


#endif