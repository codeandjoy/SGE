#ifndef STATE_H
#define STATE_H

#include <functional>
#include <string>


namespace sge{
    class StateCluster;
    class Entity;

    class State{
        public:
            State(Entity* ownerEntity) : m_ownerEntityPtr(ownerEntity){};

            virtual void enterScript(){}
            virtual void exitScript(){}
            virtual void updateScript(float dt){}

        protected:
            Entity* m_ownerEntityPtr;
    };
}


#endif