#ifndef PLAYER_STATES_H
#define PLAYER_STATES_H

#include "../../SGE.hpp"


class PlayerMovingRightState : public sge::State{
    public:
        PlayerMovingRightState(sge::Entity* playerEntity) : sge::State(playerEntity){};

        void enterScript() override{
            m_ownerEntityPtr->motionUnit->velocity.x = 100;
        }

        void updateScript(float dt) override{
            if(m_ownerEntityPtr->stateCluster->isStateActive("on_ground")){
                if(m_ownerEntityPtr->animationCluster->getCurrentTextureSequence() != "walking_right"){
                    m_ownerEntityPtr->animationCluster->setCurrentTextureSequence("walking_right");
                }
            }
        }

        void exitScript() override{
            m_ownerEntityPtr->motionUnit->velocity.x = 0;
        }
};
class PlayerMovingLeftState : public sge::State{
    public:
        PlayerMovingLeftState(sge::Entity* playerEntity) : sge::State(playerEntity){};

        void enterScript() override{
            m_ownerEntityPtr->motionUnit->velocity.x = -100;
        }

        void updateScript(float dt) override{
            if(m_ownerEntityPtr->stateCluster->isStateActive("on_ground")){
                if(m_ownerEntityPtr->animationCluster->getCurrentTextureSequence() != "walking_left"){
                    m_ownerEntityPtr->animationCluster->setCurrentTextureSequence("walking_left");
                }
            }
        }

        void exitScript() override{
            m_ownerEntityPtr->motionUnit->velocity.x = 0;
        }
};
class PlayerJumpState : public sge::State{
    public:
        PlayerJumpState(sge::Entity* playerEntity) : sge::State(playerEntity){};

        void enterScript() override{
            // Lock double jump here if needed
            m_ownerEntityPtr->motionUnit->velocity.y = -200;
            m_ownerEntityPtr->animationCluster->setCurrentTextureSequence("in_air");
        }
};
class PlayerOnGroundState : public sge::State{
    public:
        PlayerOnGroundState(sge::Entity* playerEntity) : sge::State(playerEntity){};

        void updateScript(float dt) override{
            if(!m_ownerEntityPtr->stateCluster->isStateActive("moving_right") &&
               !m_ownerEntityPtr->stateCluster->isStateActive("moving_left")){
                    
                    m_ownerEntityPtr->animationCluster->setCurrentTextureSequence("idle");
              }
        }
};


#endif